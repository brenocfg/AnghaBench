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
struct request_queue {int dummy; } ;
struct ioc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RQ_QOS_COST ; 
 int /*<<< orphan*/  rq_qos_id (struct request_queue*,int /*<<< orphan*/ ) ; 
 struct ioc* rqos_to_ioc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ioc *q_to_ioc(struct request_queue *q)
{
	return rqos_to_ioc(rq_qos_id(q, RQ_QOS_COST));
}