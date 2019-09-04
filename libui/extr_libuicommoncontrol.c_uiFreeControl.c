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
typedef  int /*<<< orphan*/  uiControl ;

/* Variables and functions */
 int /*<<< orphan*/ * uiControlParent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiprivFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiprivUserBug (char*,int /*<<< orphan*/ *) ; 

void uiFreeControl(uiControl *c)
{
	if (uiControlParent(c) != NULL)
		uiprivUserBug("You cannot destroy a uiControl while it still has a parent. (control: %p)", c);
	uiprivFree(c);
}