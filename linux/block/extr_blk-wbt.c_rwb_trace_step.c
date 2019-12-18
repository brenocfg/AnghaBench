#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rq_depth {int /*<<< orphan*/  max_depth; int /*<<< orphan*/  scale_step; } ;
struct TYPE_4__ {TYPE_1__* q; } ;
struct rq_wb {int /*<<< orphan*/  wb_normal; int /*<<< orphan*/  wb_background; int /*<<< orphan*/  cur_win_nsec; struct rq_depth rq_depth; TYPE_2__ rqos; } ;
struct backing_dev_info {int dummy; } ;
struct TYPE_3__ {struct backing_dev_info* backing_dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_wbt_step (struct backing_dev_info*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rwb_trace_step(struct rq_wb *rwb, const char *msg)
{
	struct backing_dev_info *bdi = rwb->rqos.q->backing_dev_info;
	struct rq_depth *rqd = &rwb->rq_depth;

	trace_wbt_step(bdi, msg, rqd->scale_step, rwb->cur_win_nsec,
			rwb->wb_background, rwb->wb_normal, rqd->max_depth);
}