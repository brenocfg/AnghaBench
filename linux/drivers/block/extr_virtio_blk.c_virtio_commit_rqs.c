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
struct virtio_blk_vq {int /*<<< orphan*/  vq; int /*<<< orphan*/  lock; } ;
struct virtio_blk {struct virtio_blk_vq* vqs; } ;
struct blk_mq_hw_ctx {size_t queue_num; TYPE_1__* queue; } ;
struct TYPE_2__ {struct virtio_blk* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int virtqueue_kick_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_notify (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void virtio_commit_rqs(struct blk_mq_hw_ctx *hctx)
{
	struct virtio_blk *vblk = hctx->queue->queuedata;
	struct virtio_blk_vq *vq = &vblk->vqs[hctx->queue_num];
	bool kick;

	spin_lock_irq(&vq->lock);
	kick = virtqueue_kick_prepare(vq->vq);
	spin_unlock_irq(&vq->lock);

	if (kick)
		virtqueue_notify(vq->vq);
}