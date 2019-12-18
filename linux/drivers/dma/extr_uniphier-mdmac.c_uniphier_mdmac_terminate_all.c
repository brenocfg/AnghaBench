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
struct virt_dma_chan {int /*<<< orphan*/  lock; } ;
struct uniphier_mdmac_chan {TYPE_1__* md; } ;
struct dma_chan {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uniphier_mdmac_chan* to_uniphier_mdmac_chan (struct virt_dma_chan*) ; 
 struct virt_dma_chan* to_virt_chan (struct dma_chan*) ; 
 int uniphier_mdmac_abort (struct uniphier_mdmac_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (struct virt_dma_chan*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (struct virt_dma_chan*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_terminate_vdesc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uniphier_mdmac_terminate_all(struct dma_chan *chan)
{
	struct virt_dma_chan *vc = to_virt_chan(chan);
	struct uniphier_mdmac_chan *mc = to_uniphier_mdmac_chan(vc);
	unsigned long flags;
	int ret = 0;
	LIST_HEAD(head);

	spin_lock_irqsave(&vc->lock, flags);

	if (mc->md) {
		vchan_terminate_vdesc(&mc->md->vd);
		mc->md = NULL;
		ret = uniphier_mdmac_abort(mc);
	}
	vchan_get_all_descriptors(vc, &head);

	spin_unlock_irqrestore(&vc->lock, flags);

	vchan_dma_desc_free_list(vc, &head);

	return ret;
}