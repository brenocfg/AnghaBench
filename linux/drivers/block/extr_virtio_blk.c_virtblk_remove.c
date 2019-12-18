#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct virtio_device {TYPE_2__* config; struct virtio_blk* priv; } ;
struct virtio_blk {int index; struct virtio_blk* vqs; TYPE_3__* disk; int /*<<< orphan*/  tag_set; int /*<<< orphan*/  config_work; } ;
struct TYPE_7__ {int /*<<< orphan*/  kref; } ;
struct TYPE_10__ {TYPE_1__ kobj; } ;
struct TYPE_9__ {int /*<<< orphan*/  queue; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* del_vqs ) (struct virtio_device*) ;int /*<<< orphan*/  (* reset ) (struct virtio_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_3__*) ; 
 TYPE_4__* disk_to_dev (TYPE_3__*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct virtio_blk*) ; 
 int kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_disk (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (struct virtio_device*) ; 
 int /*<<< orphan*/  stub2 (struct virtio_device*) ; 
 int /*<<< orphan*/  vd_index_ida ; 

__attribute__((used)) static void virtblk_remove(struct virtio_device *vdev)
{
	struct virtio_blk *vblk = vdev->priv;
	int index = vblk->index;
	int refc;

	/* Make sure no work handler is accessing the device. */
	flush_work(&vblk->config_work);

	del_gendisk(vblk->disk);
	blk_cleanup_queue(vblk->disk->queue);

	blk_mq_free_tag_set(&vblk->tag_set);

	/* Stop all the virtqueues. */
	vdev->config->reset(vdev);

	refc = kref_read(&disk_to_dev(vblk->disk)->kobj.kref);
	put_disk(vblk->disk);
	vdev->config->del_vqs(vdev);
	kfree(vblk->vqs);
	kfree(vblk);

	/* Only free device id if we don't have any users */
	if (refc == 1)
		ida_simple_remove(&vd_index_ida, index);
}