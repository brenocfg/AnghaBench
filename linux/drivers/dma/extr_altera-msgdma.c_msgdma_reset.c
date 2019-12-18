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
struct msgdma_device {int idle; scalar_t__ csr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MSGDMA_CSR_CONTROL ; 
 int MSGDMA_CSR_CTL_GLOBAL_INTR ; 
 int MSGDMA_CSR_CTL_RESET ; 
 int MSGDMA_CSR_CTL_STOP_ON_EARLY ; 
 int MSGDMA_CSR_CTL_STOP_ON_ERR ; 
 scalar_t__ MSGDMA_CSR_STATUS ; 
 int MSGDMA_CSR_STAT_MASK ; 
 int MSGDMA_CSR_STAT_RESETTING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static void msgdma_reset(struct msgdma_device *mdev)
{
	u32 val;
	int ret;

	/* Reset mSGDMA */
	iowrite32(MSGDMA_CSR_STAT_MASK, mdev->csr + MSGDMA_CSR_STATUS);
	iowrite32(MSGDMA_CSR_CTL_RESET, mdev->csr + MSGDMA_CSR_CONTROL);

	ret = readl_poll_timeout(mdev->csr + MSGDMA_CSR_STATUS, val,
				 (val & MSGDMA_CSR_STAT_RESETTING) == 0,
				 1, 10000);
	if (ret)
		dev_err(mdev->dev, "DMA channel did not reset\n");

	/* Clear all status bits */
	iowrite32(MSGDMA_CSR_STAT_MASK, mdev->csr + MSGDMA_CSR_STATUS);

	/* Enable the DMA controller including interrupts */
	iowrite32(MSGDMA_CSR_CTL_STOP_ON_ERR | MSGDMA_CSR_CTL_STOP_ON_EARLY |
		  MSGDMA_CSR_CTL_GLOBAL_INTR, mdev->csr + MSGDMA_CSR_CONTROL);

	mdev->idle = true;
}