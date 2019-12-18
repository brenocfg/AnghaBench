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
struct impd1_clk {int /*<<< orphan*/  pclkname; int /*<<< orphan*/  vco1name; int /*<<< orphan*/  vco2name; int /*<<< orphan*/  uartname; int /*<<< orphan*/  spiname; int /*<<< orphan*/  scname; int /*<<< orphan*/  pclk; int /*<<< orphan*/  vco1clk; int /*<<< orphan*/  vco2clk; int /*<<< orphan*/  uartclk; int /*<<< orphan*/  spiclk; int /*<<< orphan*/ * clks; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdev_drop (int /*<<< orphan*/ ) ; 
 struct impd1_clk* impd1_clks ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void integrator_impd1_clk_exit(unsigned int id)
{
	int i;
	struct impd1_clk *imc;

	if (id > 3)
		return;
	imc = &impd1_clks[id];

	for (i = 0; i < ARRAY_SIZE(imc->clks); i++)
		clkdev_drop(imc->clks[i]);
	clk_unregister(imc->spiclk);
	clk_unregister(imc->uartclk);
	clk_unregister(imc->vco2clk);
	clk_unregister(imc->vco1clk);
	clk_unregister(imc->pclk);
	kfree(imc->scname);
	kfree(imc->spiname);
	kfree(imc->uartname);
	kfree(imc->vco2name);
	kfree(imc->vco1name);
	kfree(imc->pclkname);
}