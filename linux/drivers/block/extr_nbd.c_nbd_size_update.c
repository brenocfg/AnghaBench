#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct nbd_device {TYPE_2__* disk; struct nbd_config* config; } ;
struct nbd_config {int flags; int bytesize; int /*<<< orphan*/  blksize; } ;
struct block_device {int bd_invalidated; scalar_t__ bd_disk; } ;
struct TYPE_8__ {int /*<<< orphan*/  discard_alignment; int /*<<< orphan*/  discard_granularity; } ;
struct TYPE_11__ {TYPE_1__ limits; } ;
struct TYPE_10__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_9__ {TYPE_4__* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int NBD_FLAG_SEND_TRIM ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  bd_set_size (struct block_device*,int) ; 
 struct block_device* bdget_disk (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdput (struct block_device*) ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_discard_sectors (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_physical_block_size (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* nbd_to_dev (struct nbd_device*) ; 
 int /*<<< orphan*/  set_blocksize (struct block_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_capacity (TYPE_2__*,int) ; 

__attribute__((used)) static void nbd_size_update(struct nbd_device *nbd)
{
	struct nbd_config *config = nbd->config;
	struct block_device *bdev = bdget_disk(nbd->disk, 0);

	if (config->flags & NBD_FLAG_SEND_TRIM) {
		nbd->disk->queue->limits.discard_granularity = config->blksize;
		nbd->disk->queue->limits.discard_alignment = config->blksize;
		blk_queue_max_discard_sectors(nbd->disk->queue, UINT_MAX);
	}
	blk_queue_logical_block_size(nbd->disk->queue, config->blksize);
	blk_queue_physical_block_size(nbd->disk->queue, config->blksize);
	set_capacity(nbd->disk, config->bytesize >> 9);
	if (bdev) {
		if (bdev->bd_disk) {
			bd_set_size(bdev, config->bytesize);
			set_blocksize(bdev, config->blksize);
		} else
			bdev->bd_invalidated = 1;
		bdput(bdev);
	}
	kobject_uevent(&nbd_to_dev(nbd)->kobj, KOBJ_CHANGE);
}