#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct blkfront_ring_info {int /*<<< orphan*/  work; int /*<<< orphan*/  callback; } ;
struct blkfront_info {unsigned int nr_rings; TYPE_1__* gd; int /*<<< orphan*/ * rq; int /*<<< orphan*/  tag_set; struct blkfront_ring_info* rinfo; } ;
struct TYPE_3__ {unsigned int first_minor; unsigned int minors; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_stop_hw_queues (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_1__*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_cancel_free_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_disk (TYPE_1__*) ; 
 int /*<<< orphan*/  xlbd_release_minors (unsigned int,unsigned int) ; 

__attribute__((used)) static void xlvbd_release_gendisk(struct blkfront_info *info)
{
	unsigned int minor, nr_minors, i;

	if (info->rq == NULL)
		return;

	/* No more blkif_request(). */
	blk_mq_stop_hw_queues(info->rq);

	for (i = 0; i < info->nr_rings; i++) {
		struct blkfront_ring_info *rinfo = &info->rinfo[i];

		/* No more gnttab callback work. */
		gnttab_cancel_free_callback(&rinfo->callback);

		/* Flush gnttab callback work. Must be done with no locks held. */
		flush_work(&rinfo->work);
	}

	del_gendisk(info->gd);

	minor = info->gd->first_minor;
	nr_minors = info->gd->minors;
	xlbd_release_minors(minor, nr_minors);

	blk_cleanup_queue(info->rq);
	blk_mq_free_tag_set(&info->tag_set);
	info->rq = NULL;

	put_disk(info->gd);
	info->gd = NULL;
}