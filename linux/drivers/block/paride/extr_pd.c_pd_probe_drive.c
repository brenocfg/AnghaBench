#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int cmd_size; int nr_hw_queues; int nr_maps; int queue_depth; int flags; int /*<<< orphan*/  numa_node; int /*<<< orphan*/ * ops; } ;
struct pd_unit {int drive; struct gendisk* gd; TYPE_1__ tag_set; int /*<<< orphan*/  name; } ;
struct pd_req {int dummy; } ;
struct gendisk {int first_minor; TYPE_2__* queue; struct pd_unit* private_data; int /*<<< orphan*/  events; int /*<<< orphan*/  major; int /*<<< orphan*/ * fops; int /*<<< orphan*/  disk_name; } ;
struct TYPE_10__ {struct pd_unit* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_BOUNCE_HIGH ; 
 int BLK_MQ_F_BLOCKING ; 
 int BLK_MQ_F_SHOULD_MERGE ; 
 int /*<<< orphan*/  DISK_EVENT_MEDIA_CHANGE ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int PD_BITS ; 
 struct gendisk* alloc_disk (int) ; 
 scalar_t__ blk_mq_alloc_tag_set (TYPE_1__*) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (TYPE_1__*) ; 
 TYPE_2__* blk_mq_init_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  blk_queue_bounce_limit (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cluster ; 
 int /*<<< orphan*/  major ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct pd_unit* pd ; 
 int /*<<< orphan*/  pd_fops ; 
 int /*<<< orphan*/  pd_identify ; 
 int /*<<< orphan*/  pd_mq_ops ; 
 scalar_t__ pd_special_command (struct pd_unit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pd_probe_drive(struct pd_unit *disk)
{
	struct gendisk *p;

	p = alloc_disk(1 << PD_BITS);
	if (!p)
		return;

	strcpy(p->disk_name, disk->name);
	p->fops = &pd_fops;
	p->major = major;
	p->first_minor = (disk - pd) << PD_BITS;
	p->events = DISK_EVENT_MEDIA_CHANGE;
	disk->gd = p;
	p->private_data = disk;

	memset(&disk->tag_set, 0, sizeof(disk->tag_set));
	disk->tag_set.ops = &pd_mq_ops;
	disk->tag_set.cmd_size = sizeof(struct pd_req);
	disk->tag_set.nr_hw_queues = 1;
	disk->tag_set.nr_maps = 1;
	disk->tag_set.queue_depth = 2;
	disk->tag_set.numa_node = NUMA_NO_NODE;
	disk->tag_set.flags = BLK_MQ_F_SHOULD_MERGE | BLK_MQ_F_BLOCKING;

	if (blk_mq_alloc_tag_set(&disk->tag_set))
		return;

	p->queue = blk_mq_init_queue(&disk->tag_set);
	if (IS_ERR(p->queue)) {
		blk_mq_free_tag_set(&disk->tag_set);
		p->queue = NULL;
		return;
	}

	p->queue->queuedata = disk;
	blk_queue_max_hw_sectors(p->queue, cluster);
	blk_queue_bounce_limit(p->queue, BLK_BOUNCE_HIGH);

	if (disk->drive == -1) {
		for (disk->drive = 0; disk->drive <= 1; disk->drive++)
			if (pd_special_command(disk, pd_identify) == 0)
				return;
	} else if (pd_special_command(disk, pd_identify) == 0)
		return;
	disk->gd = NULL;
	put_disk(p);
}