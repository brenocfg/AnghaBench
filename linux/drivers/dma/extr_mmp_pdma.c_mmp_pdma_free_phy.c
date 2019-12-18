#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct mmp_pdma_device {int /*<<< orphan*/  phy_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct mmp_pdma_chan {TYPE_2__* phy; int /*<<< orphan*/  drcmr; TYPE_1__ chan; } ;
struct TYPE_4__ {int /*<<< orphan*/ * vchan; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ DRCMR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mmp_pdma_device* to_mmp_pdma_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mmp_pdma_free_phy(struct mmp_pdma_chan *pchan)
{
	struct mmp_pdma_device *pdev = to_mmp_pdma_dev(pchan->chan.device);
	unsigned long flags;
	u32 reg;

	if (!pchan->phy)
		return;

	/* clear the channel mapping in DRCMR */
	reg = DRCMR(pchan->drcmr);
	writel(0, pchan->phy->base + reg);

	spin_lock_irqsave(&pdev->phy_lock, flags);
	pchan->phy->vchan = NULL;
	pchan->phy = NULL;
	spin_unlock_irqrestore(&pdev->phy_lock, flags);
}