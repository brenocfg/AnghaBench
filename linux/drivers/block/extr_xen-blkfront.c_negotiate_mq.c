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
struct blkfront_ring_info {int /*<<< orphan*/  ring_lock; int /*<<< orphan*/  work; struct blkfront_info* dev_info; int /*<<< orphan*/  grants; int /*<<< orphan*/  indirect_pages; } ;
struct blkfront_info {int nr_rings; struct blkfront_ring_info* rinfo; TYPE_1__* xbdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  otherend; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkif_restart_queue ; 
 struct blkfront_ring_info* kvcalloc (int,int,int /*<<< orphan*/ ) ; 
 int min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_blkif_max_queues ; 
 int /*<<< orphan*/  xenbus_dev_fatal (TYPE_1__*,int,char*) ; 
 unsigned int xenbus_read_unsigned (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int negotiate_mq(struct blkfront_info *info)
{
	unsigned int backend_max_queues;
	unsigned int i;

	BUG_ON(info->nr_rings);

	/* Check if backend supports multiple queues. */
	backend_max_queues = xenbus_read_unsigned(info->xbdev->otherend,
						  "multi-queue-max-queues", 1);
	info->nr_rings = min(backend_max_queues, xen_blkif_max_queues);
	/* We need at least one ring. */
	if (!info->nr_rings)
		info->nr_rings = 1;

	info->rinfo = kvcalloc(info->nr_rings,
			       sizeof(struct blkfront_ring_info),
			       GFP_KERNEL);
	if (!info->rinfo) {
		xenbus_dev_fatal(info->xbdev, -ENOMEM, "allocating ring_info structure");
		info->nr_rings = 0;
		return -ENOMEM;
	}

	for (i = 0; i < info->nr_rings; i++) {
		struct blkfront_ring_info *rinfo;

		rinfo = &info->rinfo[i];
		INIT_LIST_HEAD(&rinfo->indirect_pages);
		INIT_LIST_HEAD(&rinfo->grants);
		rinfo->dev_info = info;
		INIT_WORK(&rinfo->work, blkif_restart_queue);
		spin_lock_init(&rinfo->ring_lock);
	}
	return 0;
}