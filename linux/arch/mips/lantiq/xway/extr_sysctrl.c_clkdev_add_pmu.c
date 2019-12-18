#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char const* dev_id; char const* con_id; struct clk* clk; } ;
struct clk {unsigned int module; unsigned int bits; TYPE_1__ cl; int /*<<< orphan*/  (* disable ) (struct clk*) ;int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  clkdev_add (TYPE_1__*) ; 
 struct clk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_disable (struct clk*) ; 
 int /*<<< orphan*/  pmu_enable ; 

__attribute__((used)) static void clkdev_add_pmu(const char *dev, const char *con, bool deactivate,
			   unsigned int module, unsigned int bits)
{
	struct clk *clk = kzalloc(sizeof(struct clk), GFP_KERNEL);

	clk->cl.dev_id = dev;
	clk->cl.con_id = con;
	clk->cl.clk = clk;
	clk->enable = pmu_enable;
	clk->disable = pmu_disable;
	clk->module = module;
	clk->bits = bits;
	if (deactivate) {
		/*
		 * Disable it during the initialization. Module should enable
		 * when used
		 */
		pmu_disable(clk);
	}
	clkdev_add(&clk->cl);
}