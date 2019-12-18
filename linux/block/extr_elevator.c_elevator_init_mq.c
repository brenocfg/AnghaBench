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
struct request_queue {int /*<<< orphan*/  required_elevator_features; int /*<<< orphan*/  elevator; int /*<<< orphan*/  queue_flags; } ;
struct elevator_type {int /*<<< orphan*/  elevator_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_REGISTERED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_freeze_queue (struct request_queue*) ; 
 int blk_mq_init_sched (struct request_queue*,struct elevator_type*) ; 
 int /*<<< orphan*/  blk_mq_quiesce_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_unfreeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (struct request_queue*) ; 
 struct elevator_type* elevator_get_by_features (struct request_queue*) ; 
 struct elevator_type* elevator_get_default (struct request_queue*) ; 
 int /*<<< orphan*/  elevator_put (struct elevator_type*) ; 
 int /*<<< orphan*/  elv_support_iosched (struct request_queue*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void elevator_init_mq(struct request_queue *q)
{
	struct elevator_type *e;
	int err;

	if (!elv_support_iosched(q))
		return;

	WARN_ON_ONCE(test_bit(QUEUE_FLAG_REGISTERED, &q->queue_flags));

	if (unlikely(q->elevator))
		return;

	if (!q->required_elevator_features)
		e = elevator_get_default(q);
	else
		e = elevator_get_by_features(q);
	if (!e)
		return;

	blk_mq_freeze_queue(q);
	blk_mq_quiesce_queue(q);

	err = blk_mq_init_sched(q, e);

	blk_mq_unquiesce_queue(q);
	blk_mq_unfreeze_queue(q);

	if (err) {
		pr_warn("\"%s\" elevator initialization failed, "
			"falling back to \"none\"\n", e->elevator_name);
		elevator_put(e);
	}
}