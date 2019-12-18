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
 int /*<<< orphan*/  POWER_MODE_CORE_INTIDLE ; 
 int /*<<< orphan*/  pxa910_pm_enter_lowpower_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pxa910_pm_finish(void)
{
	pxa910_pm_enter_lowpower_mode(POWER_MODE_CORE_INTIDLE);
}