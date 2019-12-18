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
 int /*<<< orphan*/  RQ_QOS_LATENCY ; 
 struct rq_qos* rq_qos_id (struct request_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct rq_qos *blkcg_rq_qos(struct request_queue *q)
{
	return rq_qos_id(q, RQ_QOS_LATENCY);
}