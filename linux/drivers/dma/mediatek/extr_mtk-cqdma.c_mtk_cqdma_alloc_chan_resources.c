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
typedef  size_t u32 ;
struct mtk_cqdma_vchan {struct mtk_cqdma_pchan* pc; } ;
struct mtk_cqdma_pchan {int /*<<< orphan*/  lock; int /*<<< orphan*/  refcnt; } ;
struct mtk_cqdma_device {size_t dma_channels; struct mtk_cqdma_pchan** pc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  MTK_CQDMA_INT_EN ; 
 int /*<<< orphan*/  MTK_CQDMA_INT_EN_BIT ; 
 size_t U32_MAX ; 
 int /*<<< orphan*/  mtk_cqdma_hard_reset (struct mtk_cqdma_pchan*) ; 
 int /*<<< orphan*/  mtk_dma_set (struct mtk_cqdma_pchan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 size_t refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mtk_cqdma_device* to_cqdma_dev (struct dma_chan*) ; 
 struct mtk_cqdma_vchan* to_cqdma_vchan (struct dma_chan*) ; 

__attribute__((used)) static int mtk_cqdma_alloc_chan_resources(struct dma_chan *c)
{
	struct mtk_cqdma_device *cqdma = to_cqdma_dev(c);
	struct mtk_cqdma_vchan *vc = to_cqdma_vchan(c);
	struct mtk_cqdma_pchan *pc = NULL;
	u32 i, min_refcnt = U32_MAX, refcnt;
	unsigned long flags;

	/* allocate PC with the minimun refcount */
	for (i = 0; i < cqdma->dma_channels; ++i) {
		refcnt = refcount_read(&cqdma->pc[i]->refcnt);
		if (refcnt < min_refcnt) {
			pc = cqdma->pc[i];
			min_refcnt = refcnt;
		}
	}

	if (!pc)
		return -ENOSPC;

	spin_lock_irqsave(&pc->lock, flags);

	if (!refcount_read(&pc->refcnt)) {
		/* allocate PC when the refcount is zero */
		mtk_cqdma_hard_reset(pc);

		/* enable interrupt for this PC */
		mtk_dma_set(pc, MTK_CQDMA_INT_EN, MTK_CQDMA_INT_EN_BIT);

		/*
		 * refcount_inc would complain increment on 0; use-after-free.
		 * Thus, we need to explicitly set it as 1 initially.
		 */
		refcount_set(&pc->refcnt, 1);
	} else {
		refcount_inc(&pc->refcnt);
	}

	spin_unlock_irqrestore(&pc->lock, flags);

	vc->pc = pc;

	return 0;
}