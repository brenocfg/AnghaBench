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
struct sysc {struct clk** clocks; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct clk*) ; 
 int SYSC_OPTFCK0 ; 
 int /*<<< orphan*/  clk_disable (struct clk*) ; 

__attribute__((used)) static void sysc_disable_main_clocks(struct sysc *ddata)
{
	struct clk *clock;
	int i;

	if (!ddata->clocks)
		return;

	for (i = 0; i < SYSC_OPTFCK0; i++) {
		clock = ddata->clocks[i];
		if (IS_ERR_OR_NULL(clock))
			continue;

		clk_disable(clock);
	}
}