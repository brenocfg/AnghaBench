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
typedef  int u32 ;
struct task_struct {int dummy; } ;
struct TYPE_4__ {int idx; struct task_struct* target; scalar_t__ sample_period; } ;
struct TYPE_5__ {int config; scalar_t__ type; } ;
struct perf_event {TYPE_3__* pmu; TYPE_1__ hw; TYPE_2__ attr; } ;
struct imc_pmu {int counter_mem_size; } ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  task_ctx_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int EINVAL ; 
 int ENOENT ; 
 int IMC_EVENT_OFFSET_MASK ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct imc_pmu* imc_event_to_pmu (struct perf_event*) ; 
 int /*<<< orphan*/  perf_sw_context ; 

__attribute__((used)) static int thread_imc_event_init(struct perf_event *event)
{
	u32 config = event->attr.config;
	struct task_struct *target;
	struct imc_pmu *pmu;

	if (event->attr.type != event->pmu->type)
		return -ENOENT;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	/* Sampling not supported */
	if (event->hw.sample_period)
		return -EINVAL;

	event->hw.idx = -1;
	pmu = imc_event_to_pmu(event);

	/* Sanity check for config offset */
	if (((config & IMC_EVENT_OFFSET_MASK) > pmu->counter_mem_size))
		return -EINVAL;

	target = event->hw.target;
	if (!target)
		return -EINVAL;

	event->pmu->task_ctx_nr = perf_sw_context;
	return 0;
}