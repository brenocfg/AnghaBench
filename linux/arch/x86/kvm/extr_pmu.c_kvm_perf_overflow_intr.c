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
struct kvm_pmu {int /*<<< orphan*/  irq_work; int /*<<< orphan*/  global_status; int /*<<< orphan*/  reprogram_pmi; } ;
struct kvm_pmc {int /*<<< orphan*/  vcpu; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_PMI ; 
 int /*<<< orphan*/  KVM_REQ_PMU ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  irq_work_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_is_in_guest () ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kvm_pmu* pmc_to_pmu (struct kvm_pmc*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void kvm_perf_overflow_intr(struct perf_event *perf_event,
				   struct perf_sample_data *data,
				   struct pt_regs *regs)
{
	struct kvm_pmc *pmc = perf_event->overflow_handler_context;
	struct kvm_pmu *pmu = pmc_to_pmu(pmc);

	if (!test_and_set_bit(pmc->idx,
			      (unsigned long *)&pmu->reprogram_pmi)) {
		__set_bit(pmc->idx, (unsigned long *)&pmu->global_status);
		kvm_make_request(KVM_REQ_PMU, pmc->vcpu);

		/*
		 * Inject PMI. If vcpu was in a guest mode during NMI PMI
		 * can be ejected on a guest mode re-entry. Otherwise we can't
		 * be sure that vcpu wasn't executing hlt instruction at the
		 * time of vmexit and is not going to re-enter guest mode until
		 * woken up. So we should wake it, but this is impossible from
		 * NMI context. Do it from irq work instead.
		 */
		if (!kvm_is_in_guest())
			irq_work_queue(&pmc_to_pmu(pmc)->irq_work);
		else
			kvm_make_request(KVM_REQ_PMI, pmc->vcpu);
	}
}