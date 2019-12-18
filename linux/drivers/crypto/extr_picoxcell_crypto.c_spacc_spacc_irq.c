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
typedef  int /*<<< orphan*/  u32 ;
struct spacc_engine {scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ SPA_IRQ_STAT_REG_OFFSET ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spacc_process_done (struct spacc_engine*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t spacc_spacc_irq(int irq, void *dev)
{
	struct spacc_engine *engine = (struct spacc_engine *)dev;
	u32 spacc_irq_stat = readl(engine->regs + SPA_IRQ_STAT_REG_OFFSET);

	writel(spacc_irq_stat, engine->regs + SPA_IRQ_STAT_REG_OFFSET);
	spacc_process_done(engine);

	return IRQ_HANDLED;
}