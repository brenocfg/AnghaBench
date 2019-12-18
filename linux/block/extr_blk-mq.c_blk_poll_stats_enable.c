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
struct request_queue {int /*<<< orphan*/  poll_cb; int /*<<< orphan*/  queue_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_POLL_STATS ; 
 scalar_t__ blk_queue_flag_test_and_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_stat_add_callback (struct request_queue*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool blk_poll_stats_enable(struct request_queue *q)
{
	if (test_bit(QUEUE_FLAG_POLL_STATS, &q->queue_flags) ||
	    blk_queue_flag_test_and_set(QUEUE_FLAG_POLL_STATS, q))
		return true;
	blk_stat_add_callback(q, q->poll_cb);
	return false;
}