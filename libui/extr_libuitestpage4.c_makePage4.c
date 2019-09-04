#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uiSpinbox ;
typedef  int /*<<< orphan*/  uiSlider ;
typedef  int /*<<< orphan*/  uiButton ;
typedef  int /*<<< orphan*/  uiBox ;

/* Variables and functions */
 int /*<<< orphan*/  appendCBRB ; 
 int /*<<< orphan*/ * cbox ; 
 int /*<<< orphan*/ * editable ; 
 int /*<<< orphan*/ * newHorizontalBox () ; 
 int /*<<< orphan*/ * newVerticalBox () ; 
 int /*<<< orphan*/  onCBChanged ; 
 int /*<<< orphan*/  onECBChanged ; 
 int /*<<< orphan*/  onRBSelected ; 
 int /*<<< orphan*/  onSliderChanged ; 
 int /*<<< orphan*/  onSpinboxChanged ; 
 int /*<<< orphan*/ * pbar ; 
 int /*<<< orphan*/ * rb ; 
 int /*<<< orphan*/  selectNone ; 
 int /*<<< orphan*/  selectSecond ; 
 int /*<<< orphan*/  setSliderTooHigh ; 
 int /*<<< orphan*/  setSliderTooLow ; 
 int /*<<< orphan*/  setSpinboxTooHigh ; 
 int /*<<< orphan*/  setSpinboxTooLow ; 
 int /*<<< orphan*/ * slider ; 
 int /*<<< orphan*/ * spinbox ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiButtonOnClicked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiComboboxAppend (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  uiComboboxOnSelected (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiEditableComboboxAppend (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  uiEditableComboboxOnChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * uiNewButton (char*) ; 
 int /*<<< orphan*/ * uiNewCombobox () ; 
 int /*<<< orphan*/ * uiNewDatePicker () ; 
 int /*<<< orphan*/ * uiNewDateTimePicker () ; 
 int /*<<< orphan*/ * uiNewEditableCombobox () ; 
 int /*<<< orphan*/ * uiNewHorizontalSeparator () ; 
 int /*<<< orphan*/ * uiNewProgressBar () ; 
 int /*<<< orphan*/ * uiNewRadioButtons () ; 
 int /*<<< orphan*/ * uiNewSlider (int,int) ; 
 int /*<<< orphan*/ * uiNewSpinbox (int,int) ; 
 int /*<<< orphan*/ * uiNewTimePicker () ; 
 int /*<<< orphan*/  uiRadioButtonsAppend (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  uiRadioButtonsOnSelected (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiSliderOnChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiSpinboxOnChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

uiBox *makePage4(void)
{
	uiBox *page4;
	uiBox *hbox;
	uiSpinbox *xsb;
	uiButton *b;
	uiSlider *xsl;

	page4 = newVerticalBox();

	spinbox = uiNewSpinbox(0, 100);
	uiSpinboxOnChanged(spinbox, onSpinboxChanged, NULL);
	uiBoxAppend(page4, uiControl(spinbox), 0);

	slider = uiNewSlider(0, 100);
	uiSliderOnChanged(slider, onSliderChanged, NULL);
	uiBoxAppend(page4, uiControl(slider), 0);

	pbar = uiNewProgressBar();
	uiBoxAppend(page4, uiControl(pbar), 0);

	uiBoxAppend(page4, uiControl(uiNewHorizontalSeparator()), 0);

	hbox = newHorizontalBox();
	xsb = uiNewSpinbox(-40, 40);
	uiBoxAppend(hbox, uiControl(xsb), 0);
	b = uiNewButton("Bad Low");
	uiButtonOnClicked(b, setSpinboxTooLow, xsb);
	uiBoxAppend(hbox, uiControl(b), 0);
	b = uiNewButton("Bad High");
	uiButtonOnClicked(b, setSpinboxTooHigh, xsb);
	uiBoxAppend(hbox, uiControl(b), 0);
	uiBoxAppend(page4, uiControl(hbox), 0);

	hbox = newHorizontalBox();
	xsl = uiNewSlider(-40, 40);
	uiBoxAppend(hbox, uiControl(xsl), 0);
	b = uiNewButton("Bad Low");
	uiButtonOnClicked(b, setSliderTooLow, xsl);
	uiBoxAppend(hbox, uiControl(b), 0);
	b = uiNewButton("Bad High");
	uiButtonOnClicked(b, setSliderTooHigh, xsl);
	uiBoxAppend(hbox, uiControl(b), 0);
	uiBoxAppend(page4, uiControl(hbox), 0);

	uiBoxAppend(page4, uiControl(uiNewHorizontalSeparator()), 0);

	cbox = uiNewCombobox();
	uiComboboxAppend(cbox, "Item 1");
	uiComboboxAppend(cbox, "Item 2");
	uiComboboxAppend(cbox, "Item 3");
	uiComboboxOnSelected(cbox, onCBChanged, "noneditable");
	uiBoxAppend(page4, uiControl(cbox), 0);

	editable = uiNewEditableCombobox();
	uiEditableComboboxAppend(editable, "Editable Item 1");
	uiEditableComboboxAppend(editable, "Editable Item 2");
	uiEditableComboboxAppend(editable, "Editable Item 3");
	uiEditableComboboxOnChanged(editable, onECBChanged, "editable");
	uiBoxAppend(page4, uiControl(editable), 0);

	rb = uiNewRadioButtons();
	uiRadioButtonsAppend(rb, "Item 1");
	uiRadioButtonsAppend(rb, "Item 2");
	uiRadioButtonsAppend(rb, "Item 3");
	uiRadioButtonsOnSelected(rb, onRBSelected, NULL);
	uiBoxAppend(page4, uiControl(rb), 0);

	hbox = newHorizontalBox();
	b = uiNewButton("Append");
	uiButtonOnClicked(b, appendCBRB, NULL);
	uiBoxAppend(hbox, uiControl(b), 0);
	b = uiNewButton("Second");
	uiButtonOnClicked(b, selectSecond, NULL);
	uiBoxAppend(hbox, uiControl(b), 0);
	b = uiNewButton("None");
	uiButtonOnClicked(b, selectNone, NULL);
	uiBoxAppend(hbox, uiControl(b), 0);
	uiBoxAppend(page4, uiControl(hbox), 0);

	uiBoxAppend(page4, uiControl(uiNewHorizontalSeparator()), 0);

	uiBoxAppend(page4, uiControl(uiNewDateTimePicker()), 0);
	uiBoxAppend(page4, uiControl(uiNewDatePicker()), 0);
	uiBoxAppend(page4, uiControl(uiNewTimePicker()), 0);

	return page4;
}