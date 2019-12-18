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
struct nullb_device {scalar_t__ queue_mode; int /*<<< orphan*/ * nullb; int /*<<< orphan*/  flags; } ;
struct nullb {struct nullb_device* dev; int /*<<< orphan*/  disk; int /*<<< orphan*/ * tag_set; int /*<<< orphan*/  __tag_set; int /*<<< orphan*/  q; int /*<<< orphan*/  cur_bytes; int /*<<< orphan*/  bw_timer; int /*<<< orphan*/  list; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  LONG_MAX ; 
 int /*<<< orphan*/  NULLB_DEV_FL_THROTTLED ; 
 scalar_t__ NULL_Q_MQ ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_queues (struct nullb*) ; 
 int /*<<< orphan*/  del_gendisk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nullb*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ null_cache_active (struct nullb*) ; 
 int /*<<< orphan*/  null_free_device_storage (struct nullb_device*,int) ; 
 int /*<<< orphan*/  null_restart_queue_async (struct nullb*) ; 
 int /*<<< orphan*/  nullb_indexes ; 
 int /*<<< orphan*/  put_disk (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void null_del_dev(struct nullb *nullb)
{
	struct nullb_device *dev = nullb->dev;

	ida_simple_remove(&nullb_indexes, nullb->index);

	list_del_init(&nullb->list);

	del_gendisk(nullb->disk);

	if (test_bit(NULLB_DEV_FL_THROTTLED, &nullb->dev->flags)) {
		hrtimer_cancel(&nullb->bw_timer);
		atomic_long_set(&nullb->cur_bytes, LONG_MAX);
		null_restart_queue_async(nullb);
	}

	blk_cleanup_queue(nullb->q);
	if (dev->queue_mode == NULL_Q_MQ &&
	    nullb->tag_set == &nullb->__tag_set)
		blk_mq_free_tag_set(nullb->tag_set);
	put_disk(nullb->disk);
	cleanup_queues(nullb);
	if (null_cache_active(nullb))
		null_free_device_storage(nullb->dev, true);
	kfree(nullb);
	dev->nullb = NULL;
}