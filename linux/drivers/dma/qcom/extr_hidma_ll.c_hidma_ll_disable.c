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
struct hidma_lldev {scalar_t__ evca; scalar_t__ evch_state; scalar_t__ trch_state; scalar_t__ trca; } ;

/* Variables and functions */
 int HIDMA_CH_CONTROL_MASK ; 
 scalar_t__ HIDMA_CH_STATE (int) ; 
 int HIDMA_CH_SUSPEND ; 
 scalar_t__ HIDMA_CH_SUSPENDED ; 
 scalar_t__ HIDMA_EVCA_CTRLSTS_REG ; 
 scalar_t__ HIDMA_EVCA_IRQ_EN_REG ; 
 scalar_t__ HIDMA_TRCA_CTRLSTS_REG ; 
 int /*<<< orphan*/  hidma_ll_isenabled (struct hidma_lldev*) ; 
 int readl (scalar_t__) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int hidma_ll_disable(struct hidma_lldev *lldev)
{
	u32 val;
	int ret;

	/* The channel needs to be in working state */
	if (!hidma_ll_isenabled(lldev))
		return 0;

	val = readl(lldev->trca + HIDMA_TRCA_CTRLSTS_REG);
	val &= ~(HIDMA_CH_CONTROL_MASK << 16);
	val |= HIDMA_CH_SUSPEND << 16;
	writel(val, lldev->trca + HIDMA_TRCA_CTRLSTS_REG);

	/*
	 * Start the wait right after the suspend is confirmed.
	 * Do a polled read up to 1ms and 10ms maximum.
	 */
	ret = readl_poll_timeout(lldev->trca + HIDMA_TRCA_CTRLSTS_REG, val,
				 HIDMA_CH_STATE(val) == HIDMA_CH_SUSPENDED,
				 1000, 10000);
	if (ret)
		return ret;

	val = readl(lldev->evca + HIDMA_EVCA_CTRLSTS_REG);
	val &= ~(HIDMA_CH_CONTROL_MASK << 16);
	val |= HIDMA_CH_SUSPEND << 16;
	writel(val, lldev->evca + HIDMA_EVCA_CTRLSTS_REG);

	/*
	 * Start the wait right after the suspend is confirmed
	 * Delay up to 10ms after reset to allow DMA logic to quiesce.
	 */
	ret = readl_poll_timeout(lldev->evca + HIDMA_EVCA_CTRLSTS_REG, val,
				 HIDMA_CH_STATE(val) == HIDMA_CH_SUSPENDED,
				 1000, 10000);
	if (ret)
		return ret;

	lldev->trch_state = HIDMA_CH_SUSPENDED;
	lldev->evch_state = HIDMA_CH_SUSPENDED;

	/* disable interrupts */
	writel(0, lldev->evca + HIDMA_EVCA_IRQ_EN_REG);
	return 0;
}