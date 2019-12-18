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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct mtk_cqdma_vchan {TYPE_1__* pc; TYPE_2__ vc; } ;
struct dma_chan {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_cqdma_issue_vchan_pending (struct mtk_cqdma_vchan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mtk_cqdma_vchan* to_cqdma_vchan (struct dma_chan*) ; 
 scalar_t__ vchan_issue_pending (TYPE_2__*) ; 

__attribute__((used)) static void mtk_cqdma_issue_pending(struct dma_chan *c)
{
	struct mtk_cqdma_vchan *cvc = to_cqdma_vchan(c);
	unsigned long pc_flags;
	unsigned long vc_flags;

	/* acquire PC's lock before VS's lock for lock dependency in tasklet */
	spin_lock_irqsave(&cvc->pc->lock, pc_flags);
	spin_lock_irqsave(&cvc->vc.lock, vc_flags);

	if (vchan_issue_pending(&cvc->vc))
		mtk_cqdma_issue_vchan_pending(cvc);

	spin_unlock_irqrestore(&cvc->vc.lock, vc_flags);
	spin_unlock_irqrestore(&cvc->pc->lock, pc_flags);
}