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
struct TYPE_4__ {int /*<<< orphan*/  desc_completed; int /*<<< orphan*/  lock; } ;
struct mtk_cqdma_vchan {int issue_synchronize; TYPE_2__ vc; int /*<<< orphan*/  issue_completion; TYPE_1__* pc; } ;
struct dma_chan {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ mtk_cqdma_is_vchan_active (struct mtk_cqdma_vchan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mtk_cqdma_vchan* to_cqdma_vchan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_synchronize (TYPE_2__*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_cqdma_free_active_desc(struct dma_chan *c)
{
	struct mtk_cqdma_vchan *cvc = to_cqdma_vchan(c);
	bool sync_needed = false;
	unsigned long pc_flags;
	unsigned long vc_flags;

	/* acquire PC's lock first due to lock dependency in dma ISR */
	spin_lock_irqsave(&cvc->pc->lock, pc_flags);
	spin_lock_irqsave(&cvc->vc.lock, vc_flags);

	/* synchronization is required if this VC is active */
	if (mtk_cqdma_is_vchan_active(cvc)) {
		cvc->issue_synchronize = true;
		sync_needed = true;
	}

	spin_unlock_irqrestore(&cvc->vc.lock, vc_flags);
	spin_unlock_irqrestore(&cvc->pc->lock, pc_flags);

	/* waiting for the completion of this VC */
	if (sync_needed)
		wait_for_completion(&cvc->issue_completion);

	/* free all descriptors in list desc_completed */
	vchan_synchronize(&cvc->vc);

	WARN_ONCE(!list_empty(&cvc->vc.desc_completed),
		  "Desc pending still in list desc_completed\n");
}