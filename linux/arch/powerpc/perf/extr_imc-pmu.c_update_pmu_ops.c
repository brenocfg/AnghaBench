#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  read; void* stop; int /*<<< orphan*/  start; void* del; int /*<<< orphan*/  add; int /*<<< orphan*/  event_init; int /*<<< orphan*/  commit_txn; int /*<<< orphan*/  cancel_txn; int /*<<< orphan*/  start_txn; int /*<<< orphan*/  capabilities; int /*<<< orphan*/ ** attr_groups; int /*<<< orphan*/  task_ctx_nr; } ;
struct imc_pmu {int domain; int /*<<< orphan*/ ** attr_groups; TYPE_1__ pmu; } ;

/* Variables and functions */
 size_t IMC_CPUMASK_ATTR ; 
#define  IMC_DOMAIN_CORE 131 
#define  IMC_DOMAIN_NEST 130 
#define  IMC_DOMAIN_THREAD 129 
#define  IMC_DOMAIN_TRACE 128 
 size_t IMC_FORMAT_ATTR ; 
 int /*<<< orphan*/  PERF_PMU_CAP_NO_EXCLUDE ; 
 int /*<<< orphan*/  core_imc_event_init ; 
 int /*<<< orphan*/  imc_event_add ; 
 int /*<<< orphan*/  imc_event_start ; 
 void* imc_event_stop ; 
 int /*<<< orphan*/  imc_event_update ; 
 int /*<<< orphan*/  imc_format_group ; 
 int /*<<< orphan*/  imc_pmu_cpumask_attr_group ; 
 int /*<<< orphan*/  nest_imc_event_init ; 
 int /*<<< orphan*/  perf_invalid_context ; 
 int /*<<< orphan*/  thread_imc_event_add ; 
 void* thread_imc_event_del ; 
 int /*<<< orphan*/  thread_imc_event_init ; 
 int /*<<< orphan*/  thread_imc_pmu_cancel_txn ; 
 int /*<<< orphan*/  thread_imc_pmu_commit_txn ; 
 int /*<<< orphan*/  thread_imc_pmu_start_txn ; 
 int /*<<< orphan*/  trace_imc_event_add ; 
 void* trace_imc_event_del ; 
 int /*<<< orphan*/  trace_imc_event_init ; 
 int /*<<< orphan*/  trace_imc_event_read ; 
 int /*<<< orphan*/  trace_imc_event_start ; 
 void* trace_imc_event_stop ; 
 int /*<<< orphan*/  trace_imc_format_group ; 

__attribute__((used)) static int update_pmu_ops(struct imc_pmu *pmu)
{
	pmu->pmu.task_ctx_nr = perf_invalid_context;
	pmu->pmu.add = imc_event_add;
	pmu->pmu.del = imc_event_stop;
	pmu->pmu.start = imc_event_start;
	pmu->pmu.stop = imc_event_stop;
	pmu->pmu.read = imc_event_update;
	pmu->pmu.attr_groups = pmu->attr_groups;
	pmu->pmu.capabilities = PERF_PMU_CAP_NO_EXCLUDE;
	pmu->attr_groups[IMC_FORMAT_ATTR] = &imc_format_group;

	switch (pmu->domain) {
	case IMC_DOMAIN_NEST:
		pmu->pmu.event_init = nest_imc_event_init;
		pmu->attr_groups[IMC_CPUMASK_ATTR] = &imc_pmu_cpumask_attr_group;
		break;
	case IMC_DOMAIN_CORE:
		pmu->pmu.event_init = core_imc_event_init;
		pmu->attr_groups[IMC_CPUMASK_ATTR] = &imc_pmu_cpumask_attr_group;
		break;
	case IMC_DOMAIN_THREAD:
		pmu->pmu.event_init = thread_imc_event_init;
		pmu->pmu.add = thread_imc_event_add;
		pmu->pmu.del = thread_imc_event_del;
		pmu->pmu.start_txn = thread_imc_pmu_start_txn;
		pmu->pmu.cancel_txn = thread_imc_pmu_cancel_txn;
		pmu->pmu.commit_txn = thread_imc_pmu_commit_txn;
		break;
	case IMC_DOMAIN_TRACE:
		pmu->pmu.event_init = trace_imc_event_init;
		pmu->pmu.add = trace_imc_event_add;
		pmu->pmu.del = trace_imc_event_del;
		pmu->pmu.start = trace_imc_event_start;
		pmu->pmu.stop = trace_imc_event_stop;
		pmu->pmu.read = trace_imc_event_read;
		pmu->attr_groups[IMC_FORMAT_ATTR] = &trace_imc_format_group;
	default:
		break;
	}

	return 0;
}