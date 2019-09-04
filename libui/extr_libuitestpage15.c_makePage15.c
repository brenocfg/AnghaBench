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
typedef  int /*<<< orphan*/  uiCheckbox ;
typedef  int /*<<< orphan*/  uiButton ;
typedef  int /*<<< orphan*/  uiBox ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  borderWindowOpen ; 
 int /*<<< orphan*/  borderless ; 
 int /*<<< orphan*/ * fullscreen ; 
 int /*<<< orphan*/ * height ; 
 int /*<<< orphan*/ * newHorizontalBox () ; 
 int /*<<< orphan*/ * newVerticalBox () ; 
 int /*<<< orphan*/  onSize ; 
 int /*<<< orphan*/  setFullscreen ; 
 int /*<<< orphan*/  sizeHeight ; 
 int /*<<< orphan*/  sizeWidth ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiButtonOnClicked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiCheckboxOnToggled (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiNewButton (char*) ; 
 int /*<<< orphan*/ * uiNewCheckbox (char*) ; 
 int /*<<< orphan*/ * uiNewLabel (char*) ; 
 int /*<<< orphan*/ * uiNewSpinbox (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uiNewVerticalSeparator () ; 
 int /*<<< orphan*/  uiSpinboxOnChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiWindowOnContentSizeChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  updatesize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * width ; 

uiBox *makePage15(uiWindow *w)
{
	uiBox *page15;
	uiBox *hbox;
	uiButton *button;
	uiCheckbox *checkbox;

	page15 = newVerticalBox();

	hbox = newHorizontalBox();
	uiBoxAppend(page15, uiControl(hbox), 0);

	uiBoxAppend(hbox, uiControl(uiNewLabel("Size")), 0);
	width = uiNewSpinbox(INT_MIN, INT_MAX);
	uiBoxAppend(hbox, uiControl(width), 1);
	height = uiNewSpinbox(INT_MIN, INT_MAX);
	uiBoxAppend(hbox, uiControl(height), 1);
	fullscreen = uiNewCheckbox("Fullscreen");
	uiBoxAppend(hbox, uiControl(fullscreen), 0);

	uiSpinboxOnChanged(width, sizeWidth, w);
	uiSpinboxOnChanged(height, sizeHeight, w);
	uiCheckboxOnToggled(fullscreen, setFullscreen, w);
	uiWindowOnContentSizeChanged(w, onSize, NULL);
	updatesize(w);

	checkbox = uiNewCheckbox("Borderless");
	uiCheckboxOnToggled(checkbox, borderless, w);
	uiBoxAppend(page15, uiControl(checkbox), 0);

	button = uiNewButton("Borderless Resizes");
	uiButtonOnClicked(button, borderWindowOpen, NULL);
	uiBoxAppend(page15, uiControl(button), 0);

	hbox = newHorizontalBox();
	uiBoxAppend(page15, uiControl(hbox), 1);

	uiBoxAppend(hbox, uiControl(uiNewVerticalSeparator()), 0);

	return page15;
}