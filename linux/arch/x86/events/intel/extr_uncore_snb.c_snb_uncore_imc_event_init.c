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
struct TYPE_8__ {void* idx; } ;
struct TYPE_7__ {void* idx; } ;
struct hw_perf_event {int idx; unsigned long long last_tag; int event_base; int config; TYPE_4__ branch_reg; TYPE_3__ extra_reg; scalar_t__ sample_period; } ;
struct TYPE_6__ {int config; scalar_t__ type; scalar_t__ sample_period; } ;
struct perf_event {scalar_t__ cpu; struct hw_perf_event hw; int /*<<< orphan*/  event_caps; struct intel_uncore_box* pmu_private; TYPE_2__ attr; TYPE_1__* pmu; } ;
struct intel_uncore_pmu {scalar_t__ func_id; } ;
struct intel_uncore_box {scalar_t__ cpu; } ;
struct TYPE_5__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 void* EXTRA_REG_NONE ; 
 int /*<<< orphan*/  PERF_EV_CAP_READ_ACTIVE_PKG ; 
#define  SNB_UNCORE_PCI_IMC_DATA_READS 129 
 int SNB_UNCORE_PCI_IMC_DATA_READS_BASE ; 
#define  SNB_UNCORE_PCI_IMC_DATA_WRITES 128 
 int SNB_UNCORE_PCI_IMC_DATA_WRITES_BASE ; 
 int SNB_UNCORE_PCI_IMC_EVENT_MASK ; 
 int UNCORE_PMC_IDX_FREERUNNING ; 
 struct intel_uncore_pmu* uncore_event_to_pmu (struct perf_event*) ; 
 struct intel_uncore_box* uncore_pmu_to_box (struct intel_uncore_pmu*,scalar_t__) ; 

__attribute__((used)) static int snb_uncore_imc_event_init(struct perf_event *event)
{
	struct intel_uncore_pmu *pmu;
	struct intel_uncore_box *box;
	struct hw_perf_event *hwc = &event->hw;
	u64 cfg = event->attr.config & SNB_UNCORE_PCI_IMC_EVENT_MASK;
	int idx, base;

	if (event->attr.type != event->pmu->type)
		return -ENOENT;

	pmu = uncore_event_to_pmu(event);
	/* no device found for this pmu */
	if (pmu->func_id < 0)
		return -ENOENT;

	/* Sampling not supported yet */
	if (hwc->sample_period)
		return -EINVAL;

	/* unsupported modes and filters */
	if (event->attr.sample_period) /* no sampling */
		return -EINVAL;

	/*
	 * Place all uncore events for a particular physical package
	 * onto a single cpu
	 */
	if (event->cpu < 0)
		return -EINVAL;

	/* check only supported bits are set */
	if (event->attr.config & ~SNB_UNCORE_PCI_IMC_EVENT_MASK)
		return -EINVAL;

	box = uncore_pmu_to_box(pmu, event->cpu);
	if (!box || box->cpu < 0)
		return -EINVAL;

	event->cpu = box->cpu;
	event->pmu_private = box;

	event->event_caps |= PERF_EV_CAP_READ_ACTIVE_PKG;

	event->hw.idx = -1;
	event->hw.last_tag = ~0ULL;
	event->hw.extra_reg.idx = EXTRA_REG_NONE;
	event->hw.branch_reg.idx = EXTRA_REG_NONE;
	/*
	 * check event is known (whitelist, determines counter)
	 */
	switch (cfg) {
	case SNB_UNCORE_PCI_IMC_DATA_READS:
		base = SNB_UNCORE_PCI_IMC_DATA_READS_BASE;
		idx = UNCORE_PMC_IDX_FREERUNNING;
		break;
	case SNB_UNCORE_PCI_IMC_DATA_WRITES:
		base = SNB_UNCORE_PCI_IMC_DATA_WRITES_BASE;
		idx = UNCORE_PMC_IDX_FREERUNNING;
		break;
	default:
		return -EINVAL;
	}

	/* must be done before validate_group */
	event->hw.event_base = base;
	event->hw.idx = idx;

	/* Convert to standard encoding format for freerunning counters */
	event->hw.config = ((cfg - 1) << 8) | 0x10ff;

	/* no group validation needed, we have free running counters */

	return 0;
}