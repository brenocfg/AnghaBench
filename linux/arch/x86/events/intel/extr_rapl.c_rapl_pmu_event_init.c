#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct rapl_pmu {int /*<<< orphan*/  cpu; } ;
struct TYPE_8__ {int config; int idx; int /*<<< orphan*/  event_base; } ;
struct TYPE_7__ {int config; scalar_t__ type; scalar_t__ sample_period; } ;
struct perf_event {TYPE_3__ hw; struct rapl_pmu* pmu_private; int /*<<< orphan*/  cpu; TYPE_2__ attr; int /*<<< orphan*/  event_caps; } ;
struct TYPE_10__ {int /*<<< orphan*/  msr; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_9__ {TYPE_1__ pmu; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int NR_RAPL_DOMAINS ; 
 int /*<<< orphan*/  PERF_EV_CAP_READ_ACTIVE_PKG ; 
 int RAPL_EVENT_MASK ; 
 int array_index_nospec (long,int) ; 
 struct rapl_pmu* cpu_to_rapl_pmu (int /*<<< orphan*/ ) ; 
 int rapl_cntr_mask ; 
 TYPE_5__* rapl_msrs ; 
 TYPE_4__* rapl_pmus ; 

__attribute__((used)) static int rapl_pmu_event_init(struct perf_event *event)
{
	u64 cfg = event->attr.config & RAPL_EVENT_MASK;
	int bit, ret = 0;
	struct rapl_pmu *pmu;

	/* only look at RAPL events */
	if (event->attr.type != rapl_pmus->pmu.type)
		return -ENOENT;

	/* check only supported bits are set */
	if (event->attr.config & ~RAPL_EVENT_MASK)
		return -EINVAL;

	if (event->cpu < 0)
		return -EINVAL;

	event->event_caps |= PERF_EV_CAP_READ_ACTIVE_PKG;

	if (!cfg || cfg >= NR_RAPL_DOMAINS + 1)
		return -EINVAL;

	cfg = array_index_nospec((long)cfg, NR_RAPL_DOMAINS + 1);
	bit = cfg - 1;

	/* check event supported */
	if (!(rapl_cntr_mask & (1 << bit)))
		return -EINVAL;

	/* unsupported modes and filters */
	if (event->attr.sample_period) /* no sampling */
		return -EINVAL;

	/* must be done before validate_group */
	pmu = cpu_to_rapl_pmu(event->cpu);
	if (!pmu)
		return -EINVAL;
	event->cpu = pmu->cpu;
	event->pmu_private = pmu;
	event->hw.event_base = rapl_msrs[bit].msr;
	event->hw.config = cfg;
	event->hw.idx = bit;

	return ret;
}