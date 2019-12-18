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
typedef  int /*<<< orphan*/  uiBox ;

/* Variables and functions */
 int /*<<< orphan*/ * newHorizontalBox () ; 
 int /*<<< orphan*/ * newVerticalBox () ; 
 int /*<<< orphan*/ * newg (char*,int) ; 
 int /*<<< orphan*/ * newt (int) ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 

uiBox *makePage11(void)
{
	uiBox *page11;
	uiBox *ns;
	uiBox *s;

	page11 = newHorizontalBox();

	ns = newVerticalBox();
	uiBoxAppend(ns, uiControl(newg("", 0)), 0);
	uiBoxAppend(ns, uiControl(newg("", 1)), 0);
	uiBoxAppend(ns, uiControl(newg("Group", 0)), 0);
	uiBoxAppend(ns, uiControl(newg("Group", 1)), 0);
	uiBoxAppend(ns, uiControl(newt(0)), 0);
	uiBoxAppend(ns, uiControl(newt(1)), 0);
	uiBoxAppend(page11, uiControl(ns), 1);

	s = newVerticalBox();
	uiBoxAppend(s, uiControl(newg("", 0)), 1);
	uiBoxAppend(s, uiControl(newg("", 1)), 1);
	uiBoxAppend(s, uiControl(newg("Group", 0)), 1);
	uiBoxAppend(s, uiControl(newg("Group", 1)), 1);
	uiBoxAppend(s, uiControl(newt(0)), 1);
	uiBoxAppend(s, uiControl(newt(1)), 1);
	uiBoxAppend(page11, uiControl(s), 1);

	return page11;
}