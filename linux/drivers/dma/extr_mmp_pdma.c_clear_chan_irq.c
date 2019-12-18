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
typedef  int u32 ;
struct mmp_pdma_phy {int base; int idx; TYPE_1__* vchan; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int DCSR ; 
 int DCSR_BUSERR ; 
 int DINT ; 
 int EAGAIN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int readl (int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static int clear_chan_irq(struct mmp_pdma_phy *phy)
{
	u32 dcsr;
	u32 dint = readl(phy->base + DINT);
	u32 reg = (phy->idx << 2) + DCSR;

	if (!(dint & BIT(phy->idx)))
		return -EAGAIN;

	/* clear irq */
	dcsr = readl(phy->base + reg);
	writel(dcsr, phy->base + reg);
	if ((dcsr & DCSR_BUSERR) && (phy->vchan))
		dev_warn(phy->vchan->dev, "DCSR_BUSERR\n");

	return 0;
}