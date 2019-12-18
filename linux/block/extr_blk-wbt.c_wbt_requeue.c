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
struct rq_wb {struct request* sync_cookie; scalar_t__ sync_issue; } ;
struct rq_qos {int dummy; } ;
struct request {int dummy; } ;

/* Variables and functions */
 struct rq_wb* RQWB (struct rq_qos*) ; 
 int /*<<< orphan*/  rwb_enabled (struct rq_wb*) ; 

__attribute__((used)) static void wbt_requeue(struct rq_qos *rqos, struct request *rq)
{
	struct rq_wb *rwb = RQWB(rqos);
	if (!rwb_enabled(rwb))
		return;
	if (rq == rwb->sync_cookie) {
		rwb->sync_issue = 0;
		rwb->sync_cookie = NULL;
	}
}