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
typedef  int /*<<< orphan*/  u8 ;
struct virtio_device {struct virtio_blk* priv; } ;
struct virtio_blk {TYPE_1__* disk; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_queue_write_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  revalidate_disk (TYPE_1__*) ; 
 int /*<<< orphan*/  virtblk_get_cache_mode (struct virtio_device*) ; 

__attribute__((used)) static void virtblk_update_cache_mode(struct virtio_device *vdev)
{
	u8 writeback = virtblk_get_cache_mode(vdev);
	struct virtio_blk *vblk = vdev->priv;

	blk_queue_write_cache(vblk->disk->queue, writeback, false);
	revalidate_disk(vblk->disk);
}