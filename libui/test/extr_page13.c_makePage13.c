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
typedef  int /*<<< orphan*/  uiRadioButtons ;
typedef  int /*<<< orphan*/  uiProgressBar ;
typedef  int /*<<< orphan*/  uiForm ;
typedef  int /*<<< orphan*/  uiEntry ;
typedef  int /*<<< orphan*/  uiButton ;
typedef  int /*<<< orphan*/  uiBox ;

/* Variables and functions */
 int /*<<< orphan*/  buttonClicked ; 
 int /*<<< orphan*/  deleteFirst ; 
 int /*<<< orphan*/  entryChanged ; 
 int /*<<< orphan*/ * newForm () ; 
 int /*<<< orphan*/ * newVerticalBox () ; 
 int /*<<< orphan*/  setIndeterminate ; 
 int /*<<< orphan*/  showHide ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiButtonOnClicked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiEntryOnChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiFormAppend (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * uiNewButton (char*) ; 
 int /*<<< orphan*/ * uiNewHorizontalBox ; 
 int /*<<< orphan*/ * uiNewMultilineEntry () ; 
 int /*<<< orphan*/ * uiNewPasswordEntry () ; 
 int /*<<< orphan*/ * uiNewProgressBar () ; 
 int /*<<< orphan*/ * uiNewRadioButtons () ; 
 int /*<<< orphan*/ * uiNewSearchEntry () ; 
 int /*<<< orphan*/ * uiNewVerticalBox ; 
 int /*<<< orphan*/  uiProgressBarSetValue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uiRadioButtonsAppend (int /*<<< orphan*/ *,char*) ; 

uiBox *makePage13(void)
{
	uiBox *page13;
	uiRadioButtons *rb;
	uiButton *b;
	uiForm *f;
	uiEntry *e;
	uiProgressBar *p;

	page13 = newVerticalBox();

	rb = uiNewRadioButtons();
	uiRadioButtonsAppend(rb, "Item 1");
	uiRadioButtonsAppend(rb, "Item 2");
	uiRadioButtonsAppend(rb, "Item 3");
	uiBoxAppend(page13, uiControl(rb), 0);

	rb = uiNewRadioButtons();
	uiRadioButtonsAppend(rb, "Item A");
	uiRadioButtonsAppend(rb, "Item B");
	uiBoxAppend(page13, uiControl(rb), 0);

	b = uiNewButton("Horizontal");
	uiButtonOnClicked(b, buttonClicked, uiNewHorizontalBox);
	uiBoxAppend(page13, uiControl(b), 0);

	b = uiNewButton("Vertical");
	uiButtonOnClicked(b, buttonClicked, uiNewVerticalBox);
	uiBoxAppend(page13, uiControl(b), 0);

	f = newForm();

	e = uiNewPasswordEntry();
	uiEntryOnChanged(e, entryChanged, "password");
	uiFormAppend(f, "Password Entry", uiControl(e), 0);

	e = uiNewSearchEntry();
	uiEntryOnChanged(e, entryChanged, "search");
	uiFormAppend(f, "Search Box", uiControl(e), 0);

	uiFormAppend(f, "MLE", uiControl(uiNewMultilineEntry()), 1);

	p = uiNewProgressBar();
	uiProgressBarSetValue(p, 50);
	uiBoxAppend(page13, uiControl(p), 0);
	b = uiNewButton("Toggle Indeterminate");
	uiButtonOnClicked(b, setIndeterminate, p);
	uiBoxAppend(page13, uiControl(b), 0);

	b = uiNewButton("Show/Hide");
	uiButtonOnClicked(b, showHide, e);
	uiBoxAppend(page13, uiControl(b), 0);
	b = uiNewButton("Delete First");
	uiButtonOnClicked(b, deleteFirst, f);
	uiBoxAppend(page13, uiControl(b), 0);
	uiBoxAppend(page13, uiControl(f), 1);

	return page13;
}