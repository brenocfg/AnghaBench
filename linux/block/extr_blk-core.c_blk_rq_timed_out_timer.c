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
struct timer_list {int dummy; } ;
struct request_queue {int /*<<< orphan*/  timeout_work; } ;

/* Variables and functions */
 struct request_queue* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kblockd_schedule_work (int /*<<< orphan*/ *) ; 
 struct request_queue* q ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static void blk_rq_timed_out_timer(struct timer_list *t)
{
	struct request_queue *q = from_timer(q, t, timeout);

	kblockd_schedule_work(&q->timeout_work);
}