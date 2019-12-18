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
struct mmp_pdma_phy {TYPE_1__* vchan; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ clear_chan_irq (struct mmp_pdma_phy*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mmp_pdma_chan_handler(int irq, void *dev_id)
{
	struct mmp_pdma_phy *phy = dev_id;

	if (clear_chan_irq(phy) != 0)
		return IRQ_NONE;

	tasklet_schedule(&phy->vchan->tasklet);
	return IRQ_HANDLED;
}