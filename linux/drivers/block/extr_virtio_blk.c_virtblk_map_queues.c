#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct virtio_blk {int /*<<< orphan*/  vdev; } ;
struct blk_mq_tag_set {int /*<<< orphan*/ * map; struct virtio_blk* driver_data; } ;

/* Variables and functions */
 size_t HCTX_TYPE_DEFAULT ; 
 int blk_mq_virtio_map_queues (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtblk_map_queues(struct blk_mq_tag_set *set)
{
	struct virtio_blk *vblk = set->driver_data;

	return blk_mq_virtio_map_queues(&set->map[HCTX_TYPE_DEFAULT],
					vblk->vdev, 0);
}