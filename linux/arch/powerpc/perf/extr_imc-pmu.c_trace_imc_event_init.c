#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct TYPE_6__ {int idx; struct task_struct* target; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ sample_period; } ;
struct perf_event {TYPE_1__* pmu; TYPE_3__ hw; TYPE_2__ attr; } ;
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  task_ctx_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int ENOENT ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_hw_context ; 

__attribute__((used)) static int trace_imc_event_init(struct perf_event *event)
{
	struct task_struct *target;

	if (event->attr.type != event->pmu->type)
		return -ENOENT;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	/* Return if this is a couting event */
	if (event->attr.sample_period == 0)
		return -ENOENT;

	event->hw.idx = -1;
	target = event->hw.target;

	event->pmu->task_ctx_nr = perf_hw_context;
	return 0;
}