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
typedef  int /*<<< orphan*/  uiGroup ;
typedef  int /*<<< orphan*/  uiBox ;
typedef  int /*<<< orphan*/  uiAreaHandler ;
struct TYPE_3__ {int /*<<< orphan*/  KeyEvent; int /*<<< orphan*/  DragBroken; int /*<<< orphan*/  MouseCrossed; int /*<<< orphan*/  MouseEvent; int /*<<< orphan*/  Draw; } ;
struct TYPE_4__ {TYPE_1__ ah; } ;

/* Variables and functions */
 int /*<<< orphan*/ * area ; 
 int /*<<< orphan*/  checkboxToggled ; 
 int /*<<< orphan*/  entryChanged ; 
 TYPE_2__ handler ; 
 int /*<<< orphan*/  handlerDragBroken ; 
 int /*<<< orphan*/  handlerDraw ; 
 int /*<<< orphan*/  handlerKeyEvent ; 
 int /*<<< orphan*/  handlerMouseCrossed ; 
 int /*<<< orphan*/  handlerMouseEvent ; 
 int /*<<< orphan*/ * negative ; 
 int /*<<< orphan*/ * newGroup (char*) ; 
 int /*<<< orphan*/ * newHorizontalBox () ; 
 int /*<<< orphan*/ * newVerticalBox () ; 
 int /*<<< orphan*/ * radians ; 
 int /*<<< orphan*/ * startAngle ; 
 int /*<<< orphan*/ * sweep ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiCheckboxOnToggled (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiEntryOnChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiGroupSetChild (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uiNewArea (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiNewCheckbox (char*) ; 
 int /*<<< orphan*/ * uiNewEntry () ; 
 int /*<<< orphan*/ * uiNewLabel (char*) ; 

uiGroup *makePage7a(void)
{
	uiGroup *group;
	uiBox *box, *box2;

	handler.ah.Draw = handlerDraw;
	handler.ah.MouseEvent = handlerMouseEvent;
	handler.ah.MouseCrossed = handlerMouseCrossed;
	handler.ah.DragBroken = handlerDragBroken;
	handler.ah.KeyEvent = handlerKeyEvent;

	group = newGroup("Arc Test");

	box = newVerticalBox();
	uiGroupSetChild(group, uiControl(box));

	area = uiNewArea((uiAreaHandler *) (&handler));
	uiBoxAppend(box, uiControl(area), 1);

	box2 = newHorizontalBox();
	uiBoxAppend(box, uiControl(box2), 0);

	uiBoxAppend(box2, uiControl(uiNewLabel("Start Angle")), 0);
	startAngle = uiNewEntry();
	uiEntryOnChanged(startAngle, entryChanged, NULL);
	uiBoxAppend(box2, uiControl(startAngle), 1);

	box2 = newHorizontalBox();
	uiBoxAppend(box, uiControl(box2), 0);

	uiBoxAppend(box2, uiControl(uiNewLabel("Sweep")), 0);
	sweep = uiNewEntry();
	uiEntryOnChanged(sweep, entryChanged, NULL);
	uiBoxAppend(box2, uiControl(sweep), 1);

	negative = uiNewCheckbox("Negative");
	uiCheckboxOnToggled(negative, checkboxToggled, NULL);
	uiBoxAppend(box, uiControl(negative), 0);

	radians = uiNewCheckbox("Radians");
	uiCheckboxOnToggled(radians, checkboxToggled, NULL);
	uiBoxAppend(box, uiControl(radians), 0);

	return group;
}