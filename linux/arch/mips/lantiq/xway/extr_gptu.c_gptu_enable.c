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
struct clk {size_t bits; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int BIT (size_t) ; 
 int CON_CLK_INT ; 
 int CON_CNT ; 
 int CON_EDGE_ANY ; 
 int CON_SYNC ; 
 int /*<<< orphan*/  GPTU_CON (size_t) ; 
 int /*<<< orphan*/  GPTU_IRNEN ; 
 int /*<<< orphan*/  GPTU_RLD (size_t) ; 
 int /*<<< orphan*/  GPTU_RUN (size_t) ; 
 int /*<<< orphan*/  IRQF_TIMER ; 
 int RUN_RL ; 
 int RUN_SEN ; 
 int gptu_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gptu_w32 (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* irqres ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_irq_handler ; 

__attribute__((used)) static int gptu_enable(struct clk *clk)
{
	int ret = request_irq(irqres[clk->bits].start, timer_irq_handler,
		IRQF_TIMER, "gtpu", NULL);
	if (ret) {
		pr_err("gptu: failed to request irq\n");
		return ret;
	}

	gptu_w32(CON_CNT | CON_EDGE_ANY | CON_SYNC | CON_CLK_INT,
		GPTU_CON(clk->bits));
	gptu_w32(1, GPTU_RLD(clk->bits));
	gptu_w32(gptu_r32(GPTU_IRNEN) | BIT(clk->bits), GPTU_IRNEN);
	gptu_w32(RUN_SEN | RUN_RL, GPTU_RUN(clk->bits));
	return 0;
}