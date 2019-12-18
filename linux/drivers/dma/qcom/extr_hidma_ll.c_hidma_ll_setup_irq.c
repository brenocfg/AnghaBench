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
struct hidma_lldev {int msi_support; scalar_t__ evca; } ;

/* Variables and functions */
 int ENABLE_IRQS ; 
 scalar_t__ HIDMA_EVCA_INTCTRL_REG ; 
 scalar_t__ HIDMA_EVCA_IRQ_CLR_REG ; 
 scalar_t__ HIDMA_EVCA_IRQ_EN_REG ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void hidma_ll_setup_irq(struct hidma_lldev *lldev, bool msi)
{
	u32 val;

	lldev->msi_support = msi;

	/* disable interrupts again after reset */
	writel(0, lldev->evca + HIDMA_EVCA_IRQ_CLR_REG);
	writel(0, lldev->evca + HIDMA_EVCA_IRQ_EN_REG);

	/* support IRQ by default */
	val = readl(lldev->evca + HIDMA_EVCA_INTCTRL_REG);
	val &= ~0xF;
	if (!lldev->msi_support)
		val = val | 0x1;
	writel(val, lldev->evca + HIDMA_EVCA_INTCTRL_REG);

	/* clear all pending interrupts and enable them */
	writel(ENABLE_IRQS, lldev->evca + HIDMA_EVCA_IRQ_CLR_REG);
	writel(ENABLE_IRQS, lldev->evca + HIDMA_EVCA_IRQ_EN_REG);
}