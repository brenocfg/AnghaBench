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
struct TYPE_6__ {int idx; int /*<<< orphan*/  reg; } ;
struct TYPE_7__ {TYPE_2__ extra_reg; int /*<<< orphan*/  config; } ;
struct perf_event {TYPE_3__ hw; } ;
struct TYPE_8__ {TYPE_1__* extra_regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int EXTRA_REG_RSP_0 ; 
 int EXTRA_REG_RSP_1 ; 
 int /*<<< orphan*/  INTEL_ARCH_EVENT_MASK ; 
 int /*<<< orphan*/  MSR_OFFCORE_RSP_0 ; 
 int /*<<< orphan*/  MSR_OFFCORE_RSP_1 ; 
 TYPE_4__ x86_pmu ; 

__attribute__((used)) static void intel_fixup_er(struct perf_event *event, int idx)
{
	event->hw.extra_reg.idx = idx;

	if (idx == EXTRA_REG_RSP_0) {
		event->hw.config &= ~INTEL_ARCH_EVENT_MASK;
		event->hw.config |= x86_pmu.extra_regs[EXTRA_REG_RSP_0].event;
		event->hw.extra_reg.reg = MSR_OFFCORE_RSP_0;
	} else if (idx == EXTRA_REG_RSP_1) {
		event->hw.config &= ~INTEL_ARCH_EVENT_MASK;
		event->hw.config |= x86_pmu.extra_regs[EXTRA_REG_RSP_1].event;
		event->hw.extra_reg.reg = MSR_OFFCORE_RSP_1;
	}
}