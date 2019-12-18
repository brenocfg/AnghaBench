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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct mtk_hsdma_vchan {TYPE_1__ vc; } ;
struct mtk_hsdma_device {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_hsdma_issue_vchan_pending (struct mtk_hsdma_device*,struct mtk_hsdma_vchan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mtk_hsdma_device* to_hsdma_dev (struct dma_chan*) ; 
 struct mtk_hsdma_vchan* to_hsdma_vchan (struct dma_chan*) ; 
 scalar_t__ vchan_issue_pending (TYPE_1__*) ; 

__attribute__((used)) static void mtk_hsdma_issue_pending(struct dma_chan *c)
{
	struct mtk_hsdma_device *hsdma = to_hsdma_dev(c);
	struct mtk_hsdma_vchan *hvc = to_hsdma_vchan(c);
	unsigned long flags;

	spin_lock_irqsave(&hvc->vc.lock, flags);

	if (vchan_issue_pending(&hvc->vc))
		mtk_hsdma_issue_vchan_pending(hsdma, hvc);

	spin_unlock_irqrestore(&hvc->vc.lock, flags);
}