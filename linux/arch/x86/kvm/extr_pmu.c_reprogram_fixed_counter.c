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
typedef  int /*<<< orphan*/  ulong ;
typedef  int u8 ;
struct kvm_pmu_event_filter {scalar_t__ action; int /*<<< orphan*/  fixed_counter_bitmap; } ;
struct kvm_pmc {TYPE_1__* vcpu; } ;
struct TYPE_6__ {int /*<<< orphan*/  pmu_event_filter; } ;
struct kvm {int /*<<< orphan*/  srcu; TYPE_2__ arch; } ;
struct TYPE_8__ {TYPE_3__* pmu_ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* find_fixed_event ) (int) ;} ;
struct TYPE_5__ {struct kvm* kvm; } ;

/* Variables and functions */
 scalar_t__ KVM_PMU_EVENT_ALLOW ; 
 scalar_t__ KVM_PMU_EVENT_DENY ; 
 int /*<<< orphan*/  PERF_TYPE_HARDWARE ; 
 TYPE_4__* kvm_x86_ops ; 
 int /*<<< orphan*/  pmc_is_enabled (struct kvm_pmc*) ; 
 int /*<<< orphan*/  pmc_reprogram_counter (struct kvm_pmc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  pmc_stop_counter (struct kvm_pmc*) ; 
 struct kvm_pmu_event_filter* srcu_dereference (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

void reprogram_fixed_counter(struct kvm_pmc *pmc, u8 ctrl, int idx)
{
	unsigned en_field = ctrl & 0x3;
	bool pmi = ctrl & 0x8;
	struct kvm_pmu_event_filter *filter;
	struct kvm *kvm = pmc->vcpu->kvm;

	pmc_stop_counter(pmc);

	if (!en_field || !pmc_is_enabled(pmc))
		return;

	filter = srcu_dereference(kvm->arch.pmu_event_filter, &kvm->srcu);
	if (filter) {
		if (filter->action == KVM_PMU_EVENT_DENY &&
		    test_bit(idx, (ulong *)&filter->fixed_counter_bitmap))
			return;
		if (filter->action == KVM_PMU_EVENT_ALLOW &&
		    !test_bit(idx, (ulong *)&filter->fixed_counter_bitmap))
			return;
	}

	pmc_reprogram_counter(pmc, PERF_TYPE_HARDWARE,
			      kvm_x86_ops->pmu_ops->find_fixed_event(idx),
			      !(en_field & 0x2), /* exclude user */
			      !(en_field & 0x1), /* exclude kernel */
			      pmi, false, false);
}