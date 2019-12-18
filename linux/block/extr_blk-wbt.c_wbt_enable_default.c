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
struct rq_qos {int dummy; } ;
struct request_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_BLK_WBT_MQ ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_registered (struct request_queue*) ; 
 scalar_t__ queue_is_mq (struct request_queue*) ; 
 int /*<<< orphan*/  wbt_init (struct request_queue*) ; 
 struct rq_qos* wbt_rq_qos (struct request_queue*) ; 

void wbt_enable_default(struct request_queue *q)
{
	struct rq_qos *rqos = wbt_rq_qos(q);
	/* Throttling already enabled? */
	if (rqos)
		return;

	/* Queue not registered? Maybe shutting down... */
	if (!blk_queue_registered(q))
		return;

	if (queue_is_mq(q) && IS_ENABLED(CONFIG_BLK_WBT_MQ))
		wbt_init(q);
}