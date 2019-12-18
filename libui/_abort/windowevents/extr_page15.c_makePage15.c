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
typedef  int /*<<< orphan*/  uiBox ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  button ; 
 int /*<<< orphan*/  center ; 
 int /*<<< orphan*/  hbox ; 
 int /*<<< orphan*/  moveX ; 
 int /*<<< orphan*/  moveY ; 
 int /*<<< orphan*/  newHorizontalBox () ; 
 int /*<<< orphan*/  onMove ; 
 int /*<<< orphan*/  page15 ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiButtonOnClicked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiNewButton (char*) ; 
 int /*<<< orphan*/  uiNewLabel (char*) ; 
 int /*<<< orphan*/  uiNewSpinbox (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiSpinboxOnChanged (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiWindowOnPositionChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  updatepos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x ; 
 int /*<<< orphan*/  y ; 

uiBox *makePage15(uiWindow *w)
{
	hbox = newHorizontalBox();
	// TODO if I make this 1 and not add anything else AND not call uiWindowOnPositionChanged(), on OS X the box won't be able to grow vertically
	uiBoxAppend(page15, uiControl(hbox), 0);

	uiBoxAppend(hbox, uiControl(uiNewLabel("Position")), 0);
	x = uiNewSpinbox(INT_MIN, INT_MAX);
	uiBoxAppend(hbox, uiControl(x), 1);
	y = uiNewSpinbox(INT_MIN, INT_MAX);
	uiBoxAppend(hbox, uiControl(y), 1);
	button = uiNewButton("Center");
	uiBoxAppend(hbox, uiControl(button), 0);

	uiSpinboxOnChanged(x, moveX, w);
	uiSpinboxOnChanged(y, moveY, w);
	uiButtonOnClicked(button, center, w);
	uiWindowOnPositionChanged(w, onMove, NULL);
	updatepos(w);
}