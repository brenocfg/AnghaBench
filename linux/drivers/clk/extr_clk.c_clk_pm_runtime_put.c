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
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clk_pm_runtime_put(struct clk_core *core)
{
	if (!core->rpm_enabled)
		return;

	pm_runtime_put_sync(core->dev);
}