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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwrng_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idle_work ; 
 int /*<<< orphan*/  omap3_rom_rng_ops ; 
 int /*<<< orphan*/  rng_clk ; 

__attribute__((used)) static int omap3_rom_rng_remove(struct platform_device *pdev)
{
	cancel_delayed_work_sync(&idle_work);
	hwrng_unregister(&omap3_rom_rng_ops);
	clk_disable_unprepare(rng_clk);
	return 0;
}