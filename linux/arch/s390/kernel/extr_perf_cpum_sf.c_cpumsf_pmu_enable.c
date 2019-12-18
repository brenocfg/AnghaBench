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
struct pmu {int dummy; } ;
struct hw_perf_event {int dummy; } ;
struct TYPE_5__ {scalar_t__ dear; scalar_t__ tear; int /*<<< orphan*/  interval; int /*<<< orphan*/  cd; int /*<<< orphan*/  ed; int /*<<< orphan*/  cs; int /*<<< orphan*/  es; } ;
struct cpu_hw_sf {int flags; TYPE_2__ lsctl; TYPE_1__* event; int /*<<< orphan*/  sfb; } ;
struct TYPE_6__ {int /*<<< orphan*/  lpp; } ;
struct TYPE_4__ {struct hw_perf_event hw; } ;

/* Variables and functions */
 int PMU_F_ENABLED ; 
 int PMU_F_ERR_MASK ; 
 TYPE_3__ S390_lowcore ; 
 int /*<<< orphan*/  SAMPL_DIAG_MODE (struct hw_perf_event*) ; 
 int /*<<< orphan*/  SAMPL_RATE (struct hw_perf_event*) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  cpu_hw_sf ; 
 int /*<<< orphan*/  debug_sprintf_event (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  extend_sampling_buffer (int /*<<< orphan*/ *,struct hw_perf_event*) ; 
 int /*<<< orphan*/  lpp (int /*<<< orphan*/ *) ; 
 int lsctl (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  sfb_account_overflows (struct cpu_hw_sf*,struct hw_perf_event*) ; 
 scalar_t__ sfb_has_pending_allocs (int /*<<< orphan*/ *,struct hw_perf_event*) ; 
 int /*<<< orphan*/  sfdbg ; 
 struct cpu_hw_sf* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpumsf_pmu_enable(struct pmu *pmu)
{
	struct cpu_hw_sf *cpuhw = this_cpu_ptr(&cpu_hw_sf);
	struct hw_perf_event *hwc;
	int err;

	if (cpuhw->flags & PMU_F_ENABLED)
		return;

	if (cpuhw->flags & PMU_F_ERR_MASK)
		return;

	/* Check whether to extent the sampling buffer.
	 *
	 * Two conditions trigger an increase of the sampling buffer for a
	 * perf event:
	 *    1. Postponed buffer allocations from the event initialization.
	 *    2. Sampling overflows that contribute to pending allocations.
	 *
	 * Note that the extend_sampling_buffer() function disables the sampling
	 * facility, but it can be fully re-enabled using sampling controls that
	 * have been saved in cpumsf_pmu_disable().
	 */
	if (cpuhw->event) {
		hwc = &cpuhw->event->hw;
		if (!(SAMPL_DIAG_MODE(hwc))) {
			/*
			 * Account number of overflow-designated
			 * buffer extents
			 */
			sfb_account_overflows(cpuhw, hwc);
			if (sfb_has_pending_allocs(&cpuhw->sfb, hwc))
				extend_sampling_buffer(&cpuhw->sfb, hwc);
		}
		/* Rate may be adjusted with ioctl() */
		cpuhw->lsctl.interval = SAMPL_RATE(&cpuhw->event->hw);
	}

	/* (Re)enable the PMU and sampling facility */
	cpuhw->flags |= PMU_F_ENABLED;
	barrier();

	err = lsctl(&cpuhw->lsctl);
	if (err) {
		cpuhw->flags &= ~PMU_F_ENABLED;
		pr_err("Loading sampling controls failed: op=%i err=%i\n",
			1, err);
		return;
	}

	/* Load current program parameter */
	lpp(&S390_lowcore.lpp);

	debug_sprintf_event(sfdbg, 6, "pmu_enable: es=%i cs=%i ed=%i cd=%i "
			    "interval:%lx tear=%p dear=%p\n",
			    cpuhw->lsctl.es, cpuhw->lsctl.cs, cpuhw->lsctl.ed,
			    cpuhw->lsctl.cd, cpuhw->lsctl.interval,
			    (void *) cpuhw->lsctl.tear,
			    (void *) cpuhw->lsctl.dear);
}