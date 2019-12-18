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
struct sa11x0_dma_phy {int dcsr; scalar_t__ base; void** dbt; void** dbs; } ;
struct sa11x0_dma_dev {struct sa11x0_dma_phy* phy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DCSR_BIU ; 
 int DCSR_IE ; 
 int DCSR_RUN ; 
 int DCSR_STRTA ; 
 int DCSR_STRTB ; 
 scalar_t__ DMA_DBSA ; 
 scalar_t__ DMA_DBSB ; 
 scalar_t__ DMA_DBTA ; 
 scalar_t__ DMA_DBTB ; 
 scalar_t__ DMA_DCSR_C ; 
 scalar_t__ DMA_DCSR_R ; 
 unsigned int NR_PHY_CHAN ; 
 struct sa11x0_dma_dev* dev_get_drvdata (struct device*) ; 
 void* readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sa11x0_dma_suspend(struct device *dev)
{
	struct sa11x0_dma_dev *d = dev_get_drvdata(dev);
	unsigned pch;

	for (pch = 0; pch < NR_PHY_CHAN; pch++) {
		struct sa11x0_dma_phy *p = &d->phy[pch];
		u32 dcsr, saved_dcsr;

		dcsr = saved_dcsr = readl_relaxed(p->base + DMA_DCSR_R);
		if (dcsr & DCSR_RUN) {
			writel(DCSR_RUN | DCSR_IE, p->base + DMA_DCSR_C);
			dcsr = readl_relaxed(p->base + DMA_DCSR_R);
		}

		saved_dcsr &= DCSR_RUN | DCSR_IE;
		if (dcsr & DCSR_BIU) {
			p->dbs[0] = readl_relaxed(p->base + DMA_DBSB);
			p->dbt[0] = readl_relaxed(p->base + DMA_DBTB);
			p->dbs[1] = readl_relaxed(p->base + DMA_DBSA);
			p->dbt[1] = readl_relaxed(p->base + DMA_DBTA);
			saved_dcsr |= (dcsr & DCSR_STRTA ? DCSR_STRTB : 0) |
				      (dcsr & DCSR_STRTB ? DCSR_STRTA : 0);
		} else {
			p->dbs[0] = readl_relaxed(p->base + DMA_DBSA);
			p->dbt[0] = readl_relaxed(p->base + DMA_DBTA);
			p->dbs[1] = readl_relaxed(p->base + DMA_DBSB);
			p->dbt[1] = readl_relaxed(p->base + DMA_DBTB);
			saved_dcsr |= dcsr & (DCSR_STRTA | DCSR_STRTB);
		}
		p->dcsr = saved_dcsr;

		writel(DCSR_STRTA | DCSR_STRTB, p->base + DMA_DCSR_C);
	}

	return 0;
}