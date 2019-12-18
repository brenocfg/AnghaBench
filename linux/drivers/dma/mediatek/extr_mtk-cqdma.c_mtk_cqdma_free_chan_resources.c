#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mtk_cqdma_vchan {TYPE_1__* pc; } ;
struct dma_chan {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_CQDMA_FLUSH ; 
 int /*<<< orphan*/  MTK_CQDMA_FLUSH_BIT ; 
 int /*<<< orphan*/  MTK_CQDMA_INT_EN ; 
 int /*<<< orphan*/  MTK_CQDMA_INT_EN_BIT ; 
 int /*<<< orphan*/  MTK_CQDMA_INT_FLAG ; 
 int /*<<< orphan*/  MTK_CQDMA_INT_FLAG_BIT ; 
 int /*<<< orphan*/  cqdma2dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mtk_cqdma_poll_engine_done (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mtk_cqdma_terminate_all (struct dma_chan*) ; 
 int /*<<< orphan*/  mtk_dma_clr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_dma_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  to_cqdma_dev (struct dma_chan*) ; 
 struct mtk_cqdma_vchan* to_cqdma_vchan (struct dma_chan*) ; 

__attribute__((used)) static void mtk_cqdma_free_chan_resources(struct dma_chan *c)
{
	struct mtk_cqdma_vchan *cvc = to_cqdma_vchan(c);
	unsigned long flags;

	/* free all descriptors in all lists on the VC */
	mtk_cqdma_terminate_all(c);

	spin_lock_irqsave(&cvc->pc->lock, flags);

	/* PC is not freed until there is no VC mapped to it */
	if (refcount_dec_and_test(&cvc->pc->refcnt)) {
		/* start the flush operation and stop the engine */
		mtk_dma_set(cvc->pc, MTK_CQDMA_FLUSH, MTK_CQDMA_FLUSH_BIT);

		/* wait for the completion of flush operation */
		if (mtk_cqdma_poll_engine_done(cvc->pc, true) < 0)
			dev_err(cqdma2dev(to_cqdma_dev(c)), "cqdma flush timeout\n");

		/* clear the flush bit and interrupt flag */
		mtk_dma_clr(cvc->pc, MTK_CQDMA_FLUSH, MTK_CQDMA_FLUSH_BIT);
		mtk_dma_clr(cvc->pc, MTK_CQDMA_INT_FLAG,
			    MTK_CQDMA_INT_FLAG_BIT);

		/* disable interrupt for this PC */
		mtk_dma_clr(cvc->pc, MTK_CQDMA_INT_EN, MTK_CQDMA_INT_EN_BIT);
	}

	spin_unlock_irqrestore(&cvc->pc->lock, flags);
}