#include "BasicKnob.h"

BasicKnob::BasicKnob(float minValue, float maxValue, const String& unit)
    : Slider(), unitOfMeasure(unit)
{
    fillColour = Colours::lightgrey;
    outlineColour = Colours::darkgrey;
    pointerColour = Colours::whitesmoke;
    setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    setRange(minValue, maxValue);
    setTextBoxStyle(NoTextBox, false, 0, 0);
}


double BasicKnob::getValueFromText(const String& text)
{
    auto valueText = text.upToFirstOccurrenceOf(" ", false, false).trim();
    return valueText.getDoubleValue();
}

String BasicKnob::getTextFromValue(double value)
{
    String text = String(value);
    if (unitOfMeasure.isNotEmpty()) text += " " + unitOfMeasure;
    return text;
}


// Change the look of JUCE's "rotary sliders" so they're more like traditional knobs. This code is adapted
// from the example at https://www.juce.com/doc/tutorial_look_and_feel_customisation.
void BasicLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height,
                                        float sliderPos, const float rotaryStartAngle,
                                        const float rotaryEndAngle, Slider& slider)
{
    auto radius = jmin(width / 2, height / 2) - 4;
    auto centreX = x + width * 0.5f;
    auto centreY = y + height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // Fill color (adjust here if necessary)
    g.setColour(Colours::darkgrey);  // You can change this to match your UI background
    g.fillEllipse(rx, ry, rw, rw);

    // Drawing the pointer
    Path p;
    const float pointerLength = radius * 0.6f;
    const float pointerThickness = 7.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));

    g.setColour(Colours::whitesmoke);
    g.fillPath(p);

    // Outline (remove this block if you do not want an outline)
    g.setColour(Colours::black);
    g.drawEllipse(rx, ry, rw, rw, 1.0f);
}


