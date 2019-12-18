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

/* Variables and functions */
 int GT_CTRL_ENABLE ; 
 int get_ctrl (int) ; 
 int /*<<< orphan*/  set_ctrl (int,int) ; 

__attribute__((used)) static void
arm_tmr_disable(bool physical)
{
	int ctrl;

	ctrl = get_ctrl(physical);
	ctrl &= ~GT_CTRL_ENABLE;
	set_ctrl(ctrl, physical);
}