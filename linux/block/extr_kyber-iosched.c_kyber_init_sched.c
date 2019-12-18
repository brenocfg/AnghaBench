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
struct request_queue {struct elevator_queue* elevator; } ;
struct kyber_queue_data {int dummy; } ;
struct elevator_type {int dummy; } ;
struct elevator_queue {struct kyber_queue_data* elevator_data; int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct kyber_queue_data*) ; 
 int PTR_ERR (struct kyber_queue_data*) ; 
 int /*<<< orphan*/  blk_stat_enable_accounting (struct request_queue*) ; 
 struct elevator_queue* elevator_alloc (struct request_queue*,struct elevator_type*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 struct kyber_queue_data* kyber_queue_data_alloc (struct request_queue*) ; 

__attribute__((used)) static int kyber_init_sched(struct request_queue *q, struct elevator_type *e)
{
	struct kyber_queue_data *kqd;
	struct elevator_queue *eq;

	eq = elevator_alloc(q, e);
	if (!eq)
		return -ENOMEM;

	kqd = kyber_queue_data_alloc(q);
	if (IS_ERR(kqd)) {
		kobject_put(&eq->kobj);
		return PTR_ERR(kqd);
	}

	blk_stat_enable_accounting(q);

	eq->elevator_data = kqd;
	q->elevator = eq;

	return 0;
}