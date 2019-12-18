#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_5__ {int idx; int config; int /*<<< orphan*/  event_base; } ;
struct TYPE_7__ {int config; scalar_t__ type; scalar_t__ sample_period; } ;
struct perf_event {TYPE_1__ hw; TYPE_3__ attr; TYPE_2__* pmu; } ;
struct TYPE_8__ {int /*<<< orphan*/  msr; } ;
struct TYPE_6__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int PERF_MSR_EVENT_MAX ; 
 int array_index_nospec (unsigned long,int) ; 
 TYPE_4__* msr ; 
 int msr_mask ; 

__attribute__((used)) static int msr_event_init(struct perf_event *event)
{
	u64 cfg = event->attr.config;

	if (event->attr.type != event->pmu->type)
		return -ENOENT;

	/* unsupported modes and filters */
	if (event->attr.sample_period) /* no sampling */
		return -EINVAL;

	if (cfg >= PERF_MSR_EVENT_MAX)
		return -EINVAL;

	cfg = array_index_nospec((unsigned long)cfg, PERF_MSR_EVENT_MAX);

	if (!(msr_mask & (1 << cfg)))
		return -EINVAL;

	event->hw.idx		= -1;
	event->hw.event_base	= msr[cfg].msr;
	event->hw.config	= cfg;

	return 0;
}