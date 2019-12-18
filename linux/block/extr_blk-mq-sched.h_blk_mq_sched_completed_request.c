#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct request {TYPE_1__* q; } ;
struct elevator_queue {TYPE_3__* type; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* completed_request ) (struct request*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {struct elevator_queue* elevator; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void blk_mq_sched_completed_request(struct request *rq, u64 now)
{
	struct elevator_queue *e = rq->q->elevator;

	if (e && e->type->ops.completed_request)
		e->type->ops.completed_request(rq, now);
}