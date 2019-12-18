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
 int /*<<< orphan*/  RQWB (struct rq_qos*) ; 
 int /*<<< orphan*/  __wbt_update_limits (int /*<<< orphan*/ ) ; 
 struct rq_qos* wbt_rq_qos (struct request_queue*) ; 

void wbt_update_limits(struct request_queue *q)
{
	struct rq_qos *rqos = wbt_rq_qos(q);
	if (!rqos)
		return;
	__wbt_update_limits(RQWB(rqos));
}