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
struct virt_dma_desc {int dummy; } ;
struct fsl_qdma_queue {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  comp_free; } ;
struct fsl_qdma_comp {int /*<<< orphan*/  list; TYPE_1__* qchan; } ;
struct TYPE_2__ {struct fsl_qdma_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct fsl_qdma_comp* to_fsl_qdma_comp (struct virt_dma_desc*) ; 

__attribute__((used)) static void fsl_qdma_free_desc(struct virt_dma_desc *vdesc)
{
	unsigned long flags;
	struct fsl_qdma_comp *fsl_comp;
	struct fsl_qdma_queue *fsl_queue;

	fsl_comp = to_fsl_qdma_comp(vdesc);
	fsl_queue = fsl_comp->qchan->queue;

	spin_lock_irqsave(&fsl_queue->queue_lock, flags);
	list_add_tail(&fsl_comp->list, &fsl_queue->comp_free);
	spin_unlock_irqrestore(&fsl_queue->queue_lock, flags);
}