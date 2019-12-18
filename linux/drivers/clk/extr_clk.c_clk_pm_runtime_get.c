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
struct clk_core {int /*<<< orphan*/  dev; int /*<<< orphan*/  rpm_enabled; } ;

/* Variables and functions */
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_pm_runtime_get(struct clk_core *core)
{
	int ret;

	if (!core->rpm_enabled)
		return 0;

	ret = pm_runtime_get_sync(core->dev);
	return ret < 0 ? ret : 0;
}