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
typedef  scalar_t__ suspend_state_t ;

/* Variables and functions */
 scalar_t__ PM_SUSPEND_MEM ; 

__attribute__((used)) static int xo1_power_state_valid(suspend_state_t pm_state)
{
	/* suspend-to-RAM only */
	return pm_state == PM_SUSPEND_MEM;
}