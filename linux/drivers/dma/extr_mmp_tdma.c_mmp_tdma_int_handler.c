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
struct mmp_tdma_device {struct mmp_tdma_chan** tdmac; } ;
struct mmp_tdma_chan {int dummy; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int TDMA_CHANNEL_NUM ; 
 int mmp_tdma_chan_handler (int,struct mmp_tdma_chan*) ; 

__attribute__((used)) static irqreturn_t mmp_tdma_int_handler(int irq, void *dev_id)
{
	struct mmp_tdma_device *tdev = dev_id;
	int i, ret;
	int irq_num = 0;

	for (i = 0; i < TDMA_CHANNEL_NUM; i++) {
		struct mmp_tdma_chan *tdmac = tdev->tdmac[i];

		ret = mmp_tdma_chan_handler(irq, tdmac);
		if (ret == IRQ_HANDLED)
			irq_num++;
	}

	if (irq_num)
		return IRQ_HANDLED;
	else
		return IRQ_NONE;
}