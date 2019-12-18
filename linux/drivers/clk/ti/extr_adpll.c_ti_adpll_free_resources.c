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
struct ti_adpll_data {struct ti_adpll_clock* clocks; } ;
struct ti_adpll_clock {int /*<<< orphan*/  clk; int /*<<< orphan*/  (* unregister ) (int /*<<< orphan*/ ) ;scalar_t__ cl; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int TI_ADPLL_M3 ; 
 int /*<<< orphan*/  clkdev_drop (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_adpll_free_resources(struct ti_adpll_data *d)
{
	int i;

	for (i = TI_ADPLL_M3; i >= 0; i--) {
		struct ti_adpll_clock *ac = &d->clocks[i];

		if (!ac || IS_ERR_OR_NULL(ac->clk))
			continue;
		if (ac->cl)
			clkdev_drop(ac->cl);
		if (ac->unregister)
			ac->unregister(ac->clk);
	}
}