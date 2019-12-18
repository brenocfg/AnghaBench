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
struct rq_qos {struct request_queue* q; int /*<<< orphan*/ * ops; int /*<<< orphan*/  id; } ;
struct request_queue {int dummy; } ;
struct blk_iolatency {int /*<<< orphan*/  timer; struct rq_qos rqos; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RQ_QOS_LATENCY ; 
 int blkcg_activate_policy (struct request_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blkcg_iolatency_ops ; 
 int /*<<< orphan*/  blkcg_policy_iolatency ; 
 int /*<<< orphan*/  blkiolatency_timer_fn ; 
 int /*<<< orphan*/  kfree (struct blk_iolatency*) ; 
 struct blk_iolatency* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_qos_add (struct request_queue*,struct rq_qos*) ; 
 int /*<<< orphan*/  rq_qos_del (struct request_queue*,struct rq_qos*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int blk_iolatency_init(struct request_queue *q)
{
	struct blk_iolatency *blkiolat;
	struct rq_qos *rqos;
	int ret;

	blkiolat = kzalloc(sizeof(*blkiolat), GFP_KERNEL);
	if (!blkiolat)
		return -ENOMEM;

	rqos = &blkiolat->rqos;
	rqos->id = RQ_QOS_LATENCY;
	rqos->ops = &blkcg_iolatency_ops;
	rqos->q = q;

	rq_qos_add(q, rqos);

	ret = blkcg_activate_policy(q, &blkcg_policy_iolatency);
	if (ret) {
		rq_qos_del(q, rqos);
		kfree(blkiolat);
		return ret;
	}

	timer_setup(&blkiolat->timer, blkiolatency_timer_fn, 0);

	return 0;
}