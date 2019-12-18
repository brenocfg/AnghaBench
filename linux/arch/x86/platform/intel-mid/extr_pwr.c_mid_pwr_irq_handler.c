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
typedef  int u32 ;
struct mid_pwr {int /*<<< orphan*/  dev; scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ PM_ICS ; 
 int /*<<< orphan*/  PM_ICS_INT_STATUS (int) ; 
 int PM_ICS_IP ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t mid_pwr_irq_handler(int irq, void *dev_id)
{
	struct mid_pwr *pwr = dev_id;
	u32 ics;

	ics = readl(pwr->regs + PM_ICS);
	if (!(ics & PM_ICS_IP))
		return IRQ_NONE;

	writel(ics | PM_ICS_IP, pwr->regs + PM_ICS);

	dev_warn(pwr->dev, "Unexpected IRQ: %#x\n", PM_ICS_INT_STATUS(ics));
	return IRQ_HANDLED;
}