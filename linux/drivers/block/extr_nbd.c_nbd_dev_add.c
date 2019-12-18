#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int max_sectors; scalar_t__ discard_alignment; scalar_t__ discard_granularity; } ;
struct request_queue {TYPE_1__ limits; } ;
struct TYPE_6__ {int nr_hw_queues; int queue_depth; int cmd_size; int flags; struct nbd_device* driver_data; int /*<<< orphan*/  numa_node; int /*<<< orphan*/ * ops; } ;
struct nbd_device {int index; TYPE_2__ tag_set; int /*<<< orphan*/  list; int /*<<< orphan*/  refs; int /*<<< orphan*/  config_refs; int /*<<< orphan*/  config_lock; int /*<<< orphan*/ * destroy_complete; struct gendisk* disk; } ;
struct nbd_cmd {int dummy; } ;
struct gendisk {int first_minor; int /*<<< orphan*/  disk_name; struct nbd_device* private_data; int /*<<< orphan*/ * fops; int /*<<< orphan*/  major; struct request_queue* queue; } ;

/* Variables and functions */
 int BLK_MQ_F_BLOCKING ; 
 int BLK_MQ_F_SHOULD_MERGE ; 
 int EEXIST ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct request_queue*) ; 
 int /*<<< orphan*/  NBD_MAJOR ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int PTR_ERR (struct request_queue*) ; 
 int /*<<< orphan*/  QUEUE_FLAG_ADD_RANDOM ; 
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  USHRT_MAX ; 
 int /*<<< orphan*/  add_disk (struct gendisk*) ; 
 struct gendisk* alloc_disk (int) ; 
 int blk_mq_alloc_tag_set (TYPE_2__*) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (TYPE_2__*) ; 
 struct request_queue* blk_mq_init_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  blk_queue_flag_clear (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_max_discard_sectors (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_queue_max_segment_size (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_segments (struct request_queue*,int /*<<< orphan*/ ) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct nbd_device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct nbd_device*) ; 
 struct nbd_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbd_fops ; 
 int /*<<< orphan*/  nbd_index_idr ; 
 int /*<<< orphan*/  nbd_mq_ops ; 
 int /*<<< orphan*/  nbd_total_devices ; 
 int part_shift ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int nbd_dev_add(int index)
{
	struct nbd_device *nbd;
	struct gendisk *disk;
	struct request_queue *q;
	int err = -ENOMEM;

	nbd = kzalloc(sizeof(struct nbd_device), GFP_KERNEL);
	if (!nbd)
		goto out;

	disk = alloc_disk(1 << part_shift);
	if (!disk)
		goto out_free_nbd;

	if (index >= 0) {
		err = idr_alloc(&nbd_index_idr, nbd, index, index + 1,
				GFP_KERNEL);
		if (err == -ENOSPC)
			err = -EEXIST;
	} else {
		err = idr_alloc(&nbd_index_idr, nbd, 0, 0, GFP_KERNEL);
		if (err >= 0)
			index = err;
	}
	if (err < 0)
		goto out_free_disk;

	nbd->index = index;
	nbd->disk = disk;
	nbd->tag_set.ops = &nbd_mq_ops;
	nbd->tag_set.nr_hw_queues = 1;
	nbd->tag_set.queue_depth = 128;
	nbd->tag_set.numa_node = NUMA_NO_NODE;
	nbd->tag_set.cmd_size = sizeof(struct nbd_cmd);
	nbd->tag_set.flags = BLK_MQ_F_SHOULD_MERGE |
		BLK_MQ_F_BLOCKING;
	nbd->tag_set.driver_data = nbd;
	nbd->destroy_complete = NULL;

	err = blk_mq_alloc_tag_set(&nbd->tag_set);
	if (err)
		goto out_free_idr;

	q = blk_mq_init_queue(&nbd->tag_set);
	if (IS_ERR(q)) {
		err = PTR_ERR(q);
		goto out_free_tags;
	}
	disk->queue = q;

	/*
	 * Tell the block layer that we are not a rotational device
	 */
	blk_queue_flag_set(QUEUE_FLAG_NONROT, disk->queue);
	blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, disk->queue);
	disk->queue->limits.discard_granularity = 0;
	disk->queue->limits.discard_alignment = 0;
	blk_queue_max_discard_sectors(disk->queue, 0);
	blk_queue_max_segment_size(disk->queue, UINT_MAX);
	blk_queue_max_segments(disk->queue, USHRT_MAX);
	blk_queue_max_hw_sectors(disk->queue, 65536);
	disk->queue->limits.max_sectors = 256;

	mutex_init(&nbd->config_lock);
	refcount_set(&nbd->config_refs, 0);
	refcount_set(&nbd->refs, 1);
	INIT_LIST_HEAD(&nbd->list);
	disk->major = NBD_MAJOR;
	disk->first_minor = index << part_shift;
	disk->fops = &nbd_fops;
	disk->private_data = nbd;
	sprintf(disk->disk_name, "nbd%d", index);
	add_disk(disk);
	nbd_total_devices++;
	return index;

out_free_tags:
	blk_mq_free_tag_set(&nbd->tag_set);
out_free_idr:
	idr_remove(&nbd_index_idr, index);
out_free_disk:
	put_disk(disk);
out_free_nbd:
	kfree(nbd);
out:
	return err;
}