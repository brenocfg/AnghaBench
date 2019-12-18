#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct virtqueue {int index; TYPE_3__* vdev; } ;
struct virtio_blk {TYPE_2__* vqs; TYPE_1__* disk; } ;
struct virtblk_req {int dummy; } ;
struct request {int dummy; } ;
struct TYPE_6__ {struct virtio_blk* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  vq; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_complete_request (struct request*) ; 
 struct request* blk_mq_rq_from_pdu (struct virtblk_req*) ; 
 int /*<<< orphan*/  blk_mq_start_stopped_hw_queues (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_disable_cb (struct virtqueue*) ; 
 int /*<<< orphan*/  virtqueue_enable_cb (struct virtqueue*) ; 
 struct virtblk_req* virtqueue_get_buf (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  virtqueue_is_broken (struct virtqueue*) ; 

__attribute__((used)) static void virtblk_done(struct virtqueue *vq)
{
	struct virtio_blk *vblk = vq->vdev->priv;
	bool req_done = false;
	int qid = vq->index;
	struct virtblk_req *vbr;
	unsigned long flags;
	unsigned int len;

	spin_lock_irqsave(&vblk->vqs[qid].lock, flags);
	do {
		virtqueue_disable_cb(vq);
		while ((vbr = virtqueue_get_buf(vblk->vqs[qid].vq, &len)) != NULL) {
			struct request *req = blk_mq_rq_from_pdu(vbr);

			blk_mq_complete_request(req);
			req_done = true;
		}
		if (unlikely(virtqueue_is_broken(vq)))
			break;
	} while (!virtqueue_enable_cb(vq));

	/* In case queue is stopped waiting for more buffers. */
	if (req_done)
		blk_mq_start_stopped_hw_queues(vblk->disk->queue, true);
	spin_unlock_irqrestore(&vblk->vqs[qid].lock, flags);
}