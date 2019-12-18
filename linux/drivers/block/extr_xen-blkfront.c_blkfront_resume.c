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
struct xenbus_device {int /*<<< orphan*/  nodename; int /*<<< orphan*/  dev; } ;
struct blkfront_ring_info {struct blk_shadow* shadow; } ;
struct blkfront_info {unsigned int nr_rings; scalar_t__ connected; int /*<<< orphan*/  tag_set; int /*<<< orphan*/  bio_list; int /*<<< orphan*/  requests; struct blkfront_ring_info* rinfo; } ;
struct blk_shadow {TYPE_1__* request; } ;
struct bio_list {int /*<<< orphan*/  tail; int /*<<< orphan*/ * head; } ;
struct TYPE_3__ {int cmd_flags; int /*<<< orphan*/ * bio; int /*<<< orphan*/  biotail; int /*<<< orphan*/  queuelist; } ;

/* Variables and functions */
 scalar_t__ BLKIF_STATE_CONNECTED ; 
 unsigned int BLK_RING_SIZE (struct blkfront_info*) ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int REQ_FUA ; 
 scalar_t__ REQ_OP_DISCARD ; 
 scalar_t__ REQ_OP_FLUSH ; 
 scalar_t__ REQ_OP_SECURE_ERASE ; 
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_list_merge (int /*<<< orphan*/ *,struct bio_list*) ; 
 int /*<<< orphan*/  blk_mq_end_request (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_update_nr_hw_queues (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  blkif_free (struct blkfront_info*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct blkfront_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ req_op (TYPE_1__*) ; 
 int talk_to_blkback (struct xenbus_device*,struct blkfront_info*) ; 

__attribute__((used)) static int blkfront_resume(struct xenbus_device *dev)
{
	struct blkfront_info *info = dev_get_drvdata(&dev->dev);
	int err = 0;
	unsigned int i, j;

	dev_dbg(&dev->dev, "blkfront_resume: %s\n", dev->nodename);

	bio_list_init(&info->bio_list);
	INIT_LIST_HEAD(&info->requests);
	for (i = 0; i < info->nr_rings; i++) {
		struct blkfront_ring_info *rinfo = &info->rinfo[i];
		struct bio_list merge_bio;
		struct blk_shadow *shadow = rinfo->shadow;

		for (j = 0; j < BLK_RING_SIZE(info); j++) {
			/* Not in use? */
			if (!shadow[j].request)
				continue;

			/*
			 * Get the bios in the request so we can re-queue them.
			 */
			if (req_op(shadow[j].request) == REQ_OP_FLUSH ||
			    req_op(shadow[j].request) == REQ_OP_DISCARD ||
			    req_op(shadow[j].request) == REQ_OP_SECURE_ERASE ||
			    shadow[j].request->cmd_flags & REQ_FUA) {
				/*
				 * Flush operations don't contain bios, so
				 * we need to requeue the whole request
				 *
				 * XXX: but this doesn't make any sense for a
				 * write with the FUA flag set..
				 */
				list_add(&shadow[j].request->queuelist, &info->requests);
				continue;
			}
			merge_bio.head = shadow[j].request->bio;
			merge_bio.tail = shadow[j].request->biotail;
			bio_list_merge(&info->bio_list, &merge_bio);
			shadow[j].request->bio = NULL;
			blk_mq_end_request(shadow[j].request, BLK_STS_OK);
		}
	}

	blkif_free(info, info->connected == BLKIF_STATE_CONNECTED);

	err = talk_to_blkback(dev, info);
	if (!err)
		blk_mq_update_nr_hw_queues(&info->tag_set, info->nr_rings);

	/*
	 * We have to wait for the backend to switch to
	 * connected state, since we want to read which
	 * features it supports.
	 */

	return err;
}