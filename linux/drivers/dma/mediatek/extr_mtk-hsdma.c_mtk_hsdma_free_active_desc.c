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
struct TYPE_2__ {int /*<<< orphan*/  desc_completed; int /*<<< orphan*/  lock; } ;
struct mtk_hsdma_vchan {int issue_synchronize; TYPE_1__ vc; int /*<<< orphan*/  desc_hw_processing; int /*<<< orphan*/  issue_completion; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct mtk_hsdma_vchan* to_hsdma_vchan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_synchronize (TYPE_1__*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_hsdma_free_active_desc(struct dma_chan *c)
{
	struct mtk_hsdma_vchan *hvc = to_hsdma_vchan(c);
	bool sync_needed = false;

	/*
	 * Once issue_synchronize is being set, which means once the hardware
	 * consumes all descriptors for the channel in the ring, the
	 * synchronization must be be notified immediately it is completed.
	 */
	spin_lock(&hvc->vc.lock);
	if (!list_empty(&hvc->desc_hw_processing)) {
		hvc->issue_synchronize = true;
		sync_needed = true;
	}
	spin_unlock(&hvc->vc.lock);

	if (sync_needed)
		wait_for_completion(&hvc->issue_completion);
	/*
	 * At the point, we expect that all remaining descriptors in the ring
	 * for the channel should be all processing done.
	 */
	WARN_ONCE(!list_empty(&hvc->desc_hw_processing),
		  "Desc pending still in list desc_hw_processing\n");

	/* Free all descriptors in list desc_completed */
	vchan_synchronize(&hvc->vc);

	WARN_ONCE(!list_empty(&hvc->vc.desc_completed),
		  "Desc pending still in list desc_completed\n");
}