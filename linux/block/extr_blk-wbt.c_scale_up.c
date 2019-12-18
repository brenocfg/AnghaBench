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
struct rq_wb {scalar_t__ unknown_cnt; int /*<<< orphan*/  rq_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  calc_wb_limits (struct rq_wb*) ; 
 int /*<<< orphan*/  rq_depth_scale_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwb_trace_step (struct rq_wb*,char*) ; 
 int /*<<< orphan*/  rwb_wake_all (struct rq_wb*) ; 

__attribute__((used)) static void scale_up(struct rq_wb *rwb)
{
	if (!rq_depth_scale_up(&rwb->rq_depth))
		return;
	calc_wb_limits(rwb);
	rwb->unknown_cnt = 0;
	rwb_wake_all(rwb);
	rwb_trace_step(rwb, "scale up");
}