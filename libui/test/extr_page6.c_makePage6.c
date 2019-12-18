#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uiButton ;
typedef  int /*<<< orphan*/  uiBox ;
typedef  int /*<<< orphan*/  uiAreaHandler ;
struct TYPE_3__ {int /*<<< orphan*/  KeyEvent; int /*<<< orphan*/  DragBroken; int /*<<< orphan*/  MouseCrossed; int /*<<< orphan*/  MouseEvent; int /*<<< orphan*/  Draw; } ;
struct TYPE_4__ {TYPE_1__ ah; } ;

/* Variables and functions */
 int /*<<< orphan*/ * area ; 
 int /*<<< orphan*/  enableArea ; 
 TYPE_2__ handler ; 
 int /*<<< orphan*/  handlerDragBroken ; 
 int /*<<< orphan*/  handlerDraw ; 
 int /*<<< orphan*/  handlerKeyEvent ; 
 int /*<<< orphan*/  handlerMouseCrossed ; 
 int /*<<< orphan*/  handlerMouseEvent ; 
 int /*<<< orphan*/ * newHorizontalBox () ; 
 int /*<<< orphan*/ * newVerticalBox () ; 
 int /*<<< orphan*/  populateComboboxWithTests (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redraw ; 
 int /*<<< orphan*/  shouldntHappen ; 
 int /*<<< orphan*/ * swallowKeys ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiButtonOnClicked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiComboboxOnSelected (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiComboboxSetSelected (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiNewArea (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiNewButton (char*) ; 
 int /*<<< orphan*/ * uiNewCheckbox (char*) ; 
 int /*<<< orphan*/ * uiNewCombobox () ; 
 int /*<<< orphan*/ * which ; 

uiBox *makePage6(void)
{
	uiBox *page6;
	uiBox *hbox;
	uiButton *button;

	handler.ah.Draw = handlerDraw;
	handler.ah.MouseEvent = handlerMouseEvent;
	handler.ah.MouseCrossed = handlerMouseCrossed;
	handler.ah.DragBroken = handlerDragBroken;
	handler.ah.KeyEvent = handlerKeyEvent;

	page6 = newVerticalBox();

	hbox = newHorizontalBox();
	uiBoxAppend(page6, uiControl(hbox), 0);

	which = uiNewCombobox();
	populateComboboxWithTests(which);
	// this is to make sure that uiComboboxOnSelected() doesn't trigger with uiComboboxSetSelected()
	uiComboboxOnSelected(which, shouldntHappen, NULL);
	uiComboboxSetSelected(which, 0);
	uiComboboxOnSelected(which, redraw, NULL);
	uiBoxAppend(hbox, uiControl(which), 0);

	area = uiNewArea((uiAreaHandler *) (&handler));
	uiBoxAppend(page6, uiControl(area), 1);

	hbox = newHorizontalBox();
	uiBoxAppend(page6, uiControl(hbox), 0);

	swallowKeys = uiNewCheckbox("Consider key events handled");
	uiBoxAppend(hbox, uiControl(swallowKeys), 1);

	button = uiNewButton("Enable");
	uiButtonOnClicked(button, enableArea, button);
	uiBoxAppend(hbox, uiControl(button), 0);

	button = uiNewButton("Disable");
	uiButtonOnClicked(button, enableArea, NULL);
	uiBoxAppend(hbox, uiControl(button), 0);

	return page6;
}