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
 int /*<<< orphan*/  PM_SUSPEND_ON ; 
 int /*<<< orphan*/  lite5200_pm_target_state ; 

__attribute__((used)) static void lite5200_pm_end(void)
{
	lite5200_pm_target_state = PM_SUSPEND_ON;
}