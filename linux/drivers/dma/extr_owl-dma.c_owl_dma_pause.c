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
struct owl_dma_vchan {TYPE_1__ vc; int /*<<< orphan*/  pchan; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  owl_dma_pause_pchan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct owl_dma_vchan* to_owl_vchan (struct dma_chan*) ; 

__attribute__((used)) static int owl_dma_pause(struct dma_chan *chan)
{
	struct owl_dma_vchan *vchan = to_owl_vchan(chan);
	unsigned long flags;

	spin_lock_irqsave(&vchan->vc.lock, flags);

	owl_dma_pause_pchan(vchan->pchan);

	spin_unlock_irqrestore(&vchan->vc.lock, flags);

	return 0;
}