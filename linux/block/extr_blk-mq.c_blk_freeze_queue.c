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

/* Variables and functions */
 int /*<<< orphan*/  blk_freeze_queue_start (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_freeze_queue_wait (struct request_queue*) ; 

void blk_freeze_queue(struct request_queue *q)
{
	/*
	 * In the !blk_mq case we are only calling this to kill the
	 * q_usage_counter, otherwise this increases the freeze depth
	 * and waits for it to return to zero.  For this reason there is
	 * no blk_unfreeze_queue(), and blk_freeze_queue() is not
	 * exported to drivers as the only user for unfreeze is blk_mq.
	 */
	blk_freeze_queue_start(q);
	blk_mq_freeze_queue_wait(q);
}