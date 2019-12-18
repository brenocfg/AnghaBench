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
 int /*<<< orphan*/  POWER_CMD_SUSPEND ; 
 int /*<<< orphan*/  power_pm_arg ; 
 int /*<<< orphan*/  power_pm_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
power_pm_deferred_fn(void *arg, int pending)
{
	int state = (intptr_t)arg;

	power_pm_fn(POWER_CMD_SUSPEND, power_pm_arg, state);
}