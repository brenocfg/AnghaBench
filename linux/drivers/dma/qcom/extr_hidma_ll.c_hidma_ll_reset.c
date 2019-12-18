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
struct hidma_lldev {scalar_t__ evch_state; scalar_t__ trch_state; scalar_t__ evca; int /*<<< orphan*/  dev; scalar_t__ trca; } ;

/* Variables and functions */
 int HIDMA_CH_CONTROL_MASK ; 
 scalar_t__ HIDMA_CH_DISABLED ; 
 int HIDMA_CH_RESET ; 
 scalar_t__ HIDMA_CH_STATE (int) ; 
 scalar_t__ HIDMA_EVCA_CTRLSTS_REG ; 
 scalar_t__ HIDMA_TRCA_CTRLSTS_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int hidma_ll_reset(struct hidma_lldev *lldev)
{
	u32 val;
	int ret;

	val = readl(lldev->trca + HIDMA_TRCA_CTRLSTS_REG);
	val &= ~(HIDMA_CH_CONTROL_MASK << 16);
	val |= HIDMA_CH_RESET << 16;
	writel(val, lldev->trca + HIDMA_TRCA_CTRLSTS_REG);

	/*
	 * Delay 10ms after reset to allow DMA logic to quiesce.
	 * Do a polled read up to 1ms and 10ms maximum.
	 */
	ret = readl_poll_timeout(lldev->trca + HIDMA_TRCA_CTRLSTS_REG, val,
				 HIDMA_CH_STATE(val) == HIDMA_CH_DISABLED,
				 1000, 10000);
	if (ret) {
		dev_err(lldev->dev, "transfer channel did not reset\n");
		return ret;
	}

	val = readl(lldev->evca + HIDMA_EVCA_CTRLSTS_REG);
	val &= ~(HIDMA_CH_CONTROL_MASK << 16);
	val |= HIDMA_CH_RESET << 16;
	writel(val, lldev->evca + HIDMA_EVCA_CTRLSTS_REG);

	/*
	 * Delay 10ms after reset to allow DMA logic to quiesce.
	 * Do a polled read up to 1ms and 10ms maximum.
	 */
	ret = readl_poll_timeout(lldev->evca + HIDMA_EVCA_CTRLSTS_REG, val,
				 HIDMA_CH_STATE(val) == HIDMA_CH_DISABLED,
				 1000, 10000);
	if (ret)
		return ret;

	lldev->trch_state = HIDMA_CH_DISABLED;
	lldev->evch_state = HIDMA_CH_DISABLED;
	return 0;
}