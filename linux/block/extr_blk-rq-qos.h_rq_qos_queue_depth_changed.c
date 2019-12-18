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
struct request_queue {scalar_t__ rq_qos; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rq_qos_queue_depth_changed (scalar_t__) ; 

__attribute__((used)) static inline void rq_qos_queue_depth_changed(struct request_queue *q)
{
	if (q->rq_qos)
		__rq_qos_queue_depth_changed(q->rq_qos);
}