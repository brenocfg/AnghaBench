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
typedef  int /*<<< orphan*/  uiWindow ;
typedef  int /*<<< orphan*/  uiLabel ;
typedef  int /*<<< orphan*/  uiButton ;
typedef  int /*<<< orphan*/  uiBox ;

/* Variables and functions */
 int /*<<< orphan*/  disableControl ; 
 int /*<<< orphan*/  enableControl ; 
 int /*<<< orphan*/ * entry ; 
 int /*<<< orphan*/  forceSpaced ; 
 int /*<<< orphan*/  getButtonText ; 
 int /*<<< orphan*/  getCheckboxText ; 
 int /*<<< orphan*/  getGroupText ; 
 int /*<<< orphan*/  getLabelText ; 
 int /*<<< orphan*/  getWindowText ; 
 int /*<<< orphan*/  hideControl ; 
 int /*<<< orphan*/ * newHorizontalBox () ; 
 int /*<<< orphan*/ * newVerticalBox () ; 
 int /*<<< orphan*/  onChanged ; 
 int /*<<< orphan*/ * page1 ; 
 int /*<<< orphan*/ * page2group ; 
 int /*<<< orphan*/  setButtonText ; 
 int /*<<< orphan*/  setCheckboxText ; 
 int /*<<< orphan*/  setGroupText ; 
 int /*<<< orphan*/  setLabelText ; 
 int /*<<< orphan*/  setWindowText ; 
 int /*<<< orphan*/  showControl ; 
 int /*<<< orphan*/  showSpaced ; 
 int /*<<< orphan*/ * spaced ; 
 int /*<<< orphan*/  toggleSpaced ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiButtonOnClicked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiCheckboxOnToggled (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiEntryOnChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiNewButton (char*) ; 
 int /*<<< orphan*/ * uiNewCheckbox (char*) ; 
 int /*<<< orphan*/ * uiNewEntry () ; 
 int /*<<< orphan*/ * uiNewLabel (char*) ; 

void makePage1(uiWindow *w)
{
	uiButton *getButton, *setButton;
	uiBox *hbox;
	uiBox *testBox;
	uiLabel *label;

	page1 = newVerticalBox();

	entry = uiNewEntry();
	uiEntryOnChanged(entry, onChanged, NULL);
	uiBoxAppend(page1, uiControl(entry), 0);

	spaced = uiNewCheckbox("Spaced");
	uiCheckboxOnToggled(spaced, toggleSpaced, NULL);
	label = uiNewLabel("Label");

	hbox = newHorizontalBox();
	getButton = uiNewButton("Get Window Text");
	uiButtonOnClicked(getButton, getWindowText, w);
	setButton = uiNewButton("Set Window Text");
	uiButtonOnClicked(setButton, setWindowText, w);
	uiBoxAppend(hbox, uiControl(getButton), 1);
	uiBoxAppend(hbox, uiControl(setButton), 1);
	uiBoxAppend(page1, uiControl(hbox), 0);

	hbox = newHorizontalBox();
	getButton = uiNewButton("Get Button Text");
	uiButtonOnClicked(getButton, getButtonText, getButton);
	setButton = uiNewButton("Set Button Text");
	uiButtonOnClicked(setButton, setButtonText, getButton);
	uiBoxAppend(hbox, uiControl(getButton), 1);
	uiBoxAppend(hbox, uiControl(setButton), 1);
	uiBoxAppend(page1, uiControl(hbox), 0);

	hbox = newHorizontalBox();
	getButton = uiNewButton("Get Checkbox Text");
	uiButtonOnClicked(getButton, getCheckboxText, spaced);
	setButton = uiNewButton("Set Checkbox Text");
	uiButtonOnClicked(setButton, setCheckboxText, spaced);
	uiBoxAppend(hbox, uiControl(getButton), 1);
	uiBoxAppend(hbox, uiControl(setButton), 1);
	uiBoxAppend(page1, uiControl(hbox), 0);

	hbox = newHorizontalBox();
	getButton = uiNewButton("Get Label Text");
	uiButtonOnClicked(getButton, getLabelText, label);
	setButton = uiNewButton("Set Label Text");
	uiButtonOnClicked(setButton, setLabelText, label);
	uiBoxAppend(hbox, uiControl(getButton), 1);
	uiBoxAppend(hbox, uiControl(setButton), 1);
	uiBoxAppend(page1, uiControl(hbox), 0);

	hbox = newHorizontalBox();
	getButton = uiNewButton("Get Group Text");
	uiButtonOnClicked(getButton, getGroupText, page2group);
	setButton = uiNewButton("Set Group Text");
	uiButtonOnClicked(setButton, setGroupText, page2group);
	uiBoxAppend(hbox, uiControl(getButton), 1);
	uiBoxAppend(hbox, uiControl(setButton), 1);
	uiBoxAppend(page1, uiControl(hbox), 0);

	hbox = newHorizontalBox();
	uiBoxAppend(hbox, uiControl(spaced), 1);
	getButton = uiNewButton("On");
	uiButtonOnClicked(getButton, forceSpaced, getButton);
	uiBoxAppend(hbox, uiControl(getButton), 0);
	getButton = uiNewButton("Off");
	uiButtonOnClicked(getButton, forceSpaced, NULL);
	uiBoxAppend(hbox, uiControl(getButton), 0);
	getButton = uiNewButton("Show");
	uiButtonOnClicked(getButton, showSpaced, NULL);
	uiBoxAppend(hbox, uiControl(getButton), 0);
	uiBoxAppend(page1, uiControl(hbox), 0);

	testBox = newHorizontalBox();
	setButton = uiNewButton("Button");
	uiBoxAppend(testBox, uiControl(setButton), 1);
	getButton = uiNewButton("Show");
	uiButtonOnClicked(getButton, showControl, setButton);
	uiBoxAppend(testBox, uiControl(getButton), 0);
	getButton = uiNewButton("Hide");
	uiButtonOnClicked(getButton, hideControl, setButton);
	uiBoxAppend(testBox, uiControl(getButton), 0);
	getButton = uiNewButton("Enable");
	uiButtonOnClicked(getButton, enableControl, setButton);
	uiBoxAppend(testBox, uiControl(getButton), 0);
	getButton = uiNewButton("Disable");
	uiButtonOnClicked(getButton, disableControl, setButton);
	uiBoxAppend(testBox, uiControl(getButton), 0);
	uiBoxAppend(page1, uiControl(testBox), 0);

	hbox = newHorizontalBox();
	getButton = uiNewButton("Show Box");
	uiButtonOnClicked(getButton, showControl, testBox);
	uiBoxAppend(hbox, uiControl(getButton), 1);
	getButton = uiNewButton("Hide Box");
	uiButtonOnClicked(getButton, hideControl, testBox);
	uiBoxAppend(hbox, uiControl(getButton), 1);
	getButton = uiNewButton("Enable Box");
	uiButtonOnClicked(getButton, enableControl, testBox);
	uiBoxAppend(hbox, uiControl(getButton), 1);
	getButton = uiNewButton("Disable Box");
	uiButtonOnClicked(getButton, disableControl, testBox);
	uiBoxAppend(hbox, uiControl(getButton), 1);
	uiBoxAppend(page1, uiControl(hbox), 0);

	uiBoxAppend(page1, uiControl(label), 0);
}