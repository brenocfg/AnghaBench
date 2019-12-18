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
struct request_queue {int dummy; } ;
struct hd_struct {int dummy; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 unsigned long jiffies_to_nsecs (unsigned long) ; 
 int /*<<< orphan*/ * nsecs ; 
 int /*<<< orphan*/  op_is_write (int) ; 
 int op_stat_group (int) ; 
 int /*<<< orphan*/  part_dec_in_flight (struct request_queue*,struct hd_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  part_stat_add (struct hd_struct*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  part_stat_lock () ; 
 int /*<<< orphan*/  part_stat_unlock () ; 
 int /*<<< orphan*/  time_in_queue ; 
 int /*<<< orphan*/  update_io_ticks (struct hd_struct*,unsigned long) ; 

void generic_end_io_acct(struct request_queue *q, int req_op,
			 struct hd_struct *part, unsigned long start_time)
{
	unsigned long now = jiffies;
	unsigned long duration = now - start_time;
	const int sgrp = op_stat_group(req_op);

	part_stat_lock();

	update_io_ticks(part, now);
	part_stat_add(part, nsecs[sgrp], jiffies_to_nsecs(duration));
	part_stat_add(part, time_in_queue, duration);
	part_dec_in_flight(q, part, op_is_write(req_op));

	part_stat_unlock();
}