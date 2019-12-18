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
struct request {struct hd_struct* part; int /*<<< orphan*/  q; TYPE_1__* rq_disk; } ;
struct hd_struct {int dummy; } ;
struct TYPE_2__ {struct hd_struct part0; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_do_io_stat (struct request*) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 struct hd_struct* disk_map_sector_rcu (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hd_struct_get (struct hd_struct*) ; 
 int /*<<< orphan*/  hd_struct_try_get (struct hd_struct*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/ * merges ; 
 int /*<<< orphan*/  part_inc_in_flight (int /*<<< orphan*/ ,struct hd_struct*,int) ; 
 int /*<<< orphan*/  part_stat_inc (struct hd_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  part_stat_lock () ; 
 int /*<<< orphan*/  part_stat_unlock () ; 
 int rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  update_io_ticks (struct hd_struct*,int /*<<< orphan*/ ) ; 

void blk_account_io_start(struct request *rq, bool new_io)
{
	struct hd_struct *part;
	int rw = rq_data_dir(rq);

	if (!blk_do_io_stat(rq))
		return;

	part_stat_lock();

	if (!new_io) {
		part = rq->part;
		part_stat_inc(part, merges[rw]);
	} else {
		part = disk_map_sector_rcu(rq->rq_disk, blk_rq_pos(rq));
		if (!hd_struct_try_get(part)) {
			/*
			 * The partition is already being removed,
			 * the request will be accounted on the disk only
			 *
			 * We take a reference on disk->part0 although that
			 * partition will never be deleted, so we can treat
			 * it as any other partition.
			 */
			part = &rq->rq_disk->part0;
			hd_struct_get(part);
		}
		part_inc_in_flight(rq->q, part, rw);
		rq->part = part;
	}

	update_io_ticks(part, jiffies);

	part_stat_unlock();
}