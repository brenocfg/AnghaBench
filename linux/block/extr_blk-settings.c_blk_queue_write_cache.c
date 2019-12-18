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
struct request_queue {int /*<<< orphan*/  queue_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_FUA ; 
 int /*<<< orphan*/  QUEUE_FLAG_WC ; 
 int /*<<< orphan*/  blk_queue_flag_clear (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wbt_set_write_cache (struct request_queue*,int /*<<< orphan*/ ) ; 

void blk_queue_write_cache(struct request_queue *q, bool wc, bool fua)
{
	if (wc)
		blk_queue_flag_set(QUEUE_FLAG_WC, q);
	else
		blk_queue_flag_clear(QUEUE_FLAG_WC, q);
	if (fua)
		blk_queue_flag_set(QUEUE_FLAG_FUA, q);
	else
		blk_queue_flag_clear(QUEUE_FLAG_FUA, q);

	wbt_set_write_cache(q, test_bit(QUEUE_FLAG_WC, &q->queue_flags));
}