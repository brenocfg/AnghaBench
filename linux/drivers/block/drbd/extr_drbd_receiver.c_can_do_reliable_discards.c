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
struct request_queue {int dummy; } ;
struct drbd_device {TYPE_1__* ldev; } ;
struct disk_conf {int discard_zeroes_if_aligned; } ;
struct TYPE_2__ {int /*<<< orphan*/  disk_conf; int /*<<< orphan*/  backing_bdev; } ;

/* Variables and functions */
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_discard (struct request_queue*) ; 
 struct disk_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static bool can_do_reliable_discards(struct drbd_device *device)
{
	struct request_queue *q = bdev_get_queue(device->ldev->backing_bdev);
	struct disk_conf *dc;
	bool can_do;

	if (!blk_queue_discard(q))
		return false;

	rcu_read_lock();
	dc = rcu_dereference(device->ldev->disk_conf);
	can_do = dc->discard_zeroes_if_aligned;
	rcu_read_unlock();
	return can_do;
}