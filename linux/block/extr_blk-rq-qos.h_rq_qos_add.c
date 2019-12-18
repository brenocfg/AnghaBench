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
struct rq_qos {TYPE_1__* ops; struct rq_qos* next; } ;
struct request_queue {struct rq_qos* rq_qos; } ;
struct TYPE_2__ {scalar_t__ debugfs_attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_debugfs_register_rqos (struct rq_qos*) ; 

__attribute__((used)) static inline void rq_qos_add(struct request_queue *q, struct rq_qos *rqos)
{
	rqos->next = q->rq_qos;
	q->rq_qos = rqos;

	if (rqos->ops->debugfs_attrs)
		blk_mq_debugfs_register_rqos(rqos);
}