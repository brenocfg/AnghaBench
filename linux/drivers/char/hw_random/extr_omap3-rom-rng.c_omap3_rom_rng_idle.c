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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RNG_RESET ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int omap3_rom_rng_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rng_clk ; 
 int rng_idle ; 

__attribute__((used)) static void omap3_rom_rng_idle(struct work_struct *work)
{
	int r;

	r = omap3_rom_rng_call(0, 0, RNG_RESET);
	if (r != 0) {
		pr_err("reset failed: %d\n", r);
		return;
	}
	clk_disable_unprepare(rng_clk);
	rng_idle = 1;
}