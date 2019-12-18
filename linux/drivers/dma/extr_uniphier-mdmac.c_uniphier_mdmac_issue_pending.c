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
struct virt_dma_chan {int /*<<< orphan*/  lock; } ;
struct uniphier_mdmac_chan {int /*<<< orphan*/  md; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uniphier_mdmac_chan* to_uniphier_mdmac_chan (struct virt_dma_chan*) ; 
 struct virt_dma_chan* to_virt_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  uniphier_mdmac_start (struct uniphier_mdmac_chan*) ; 
 scalar_t__ vchan_issue_pending (struct virt_dma_chan*) ; 

__attribute__((used)) static void uniphier_mdmac_issue_pending(struct dma_chan *chan)
{
	struct virt_dma_chan *vc = to_virt_chan(chan);
	struct uniphier_mdmac_chan *mc = to_uniphier_mdmac_chan(vc);
	unsigned long flags;

	spin_lock_irqsave(&vc->lock, flags);

	if (vchan_issue_pending(vc) && !mc->md)
		uniphier_mdmac_start(mc);

	spin_unlock_irqrestore(&vc->lock, flags);
}