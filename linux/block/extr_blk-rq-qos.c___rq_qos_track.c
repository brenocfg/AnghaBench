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
struct rq_qos {struct rq_qos* next; TYPE_1__* ops; } ;
struct request {int dummy; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* track ) (struct rq_qos*,struct request*,struct bio*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rq_qos*,struct request*,struct bio*) ; 

void __rq_qos_track(struct rq_qos *rqos, struct request *rq, struct bio *bio)
{
	do {
		if (rqos->ops->track)
			rqos->ops->track(rqos, rq, bio);
		rqos = rqos->next;
	} while (rqos);
}