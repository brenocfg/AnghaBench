#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pt_regs {int dummy; } ;
struct perf_sample_data {int dummy; } ;
struct perf_event {struct kvm_pmc* overflow_handler_context; } ;
struct kvm_pmu {int /*<<< orphan*/  global_status; int /*<<< orphan*/  reprogram_pmi; } ;
struct kvm_pmc {int /*<<< orphan*/  vcpu; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_PMU ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kvm_pmu* pmc_to_pmu (struct kvm_pmc*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void kvm_perf_overflow(struct perf_event *perf_event,
			      struct perf_sample_data *data,
			      struct pt_regs *regs)
{
	struct kvm_pmc *pmc = perf_event->overflow_handler_context;
	struct kvm_pmu *pmu = pmc_to_pmu(pmc);

	if (!test_and_set_bit(pmc->idx,
			      (unsigned long *)&pmu->reprogram_pmi)) {
		__set_bit(pmc->idx, (unsigned long *)&pmu->global_status);
		kvm_make_request(KVM_REQ_PMU, pmc->vcpu);
	}
}