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
struct kvm_nested_guest {int /*<<< orphan*/  need_tlb_flush; } ;
struct TYPE_2__ {int /*<<< orphan*/  need_tlb_flush; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int cpu_first_thread_sibling (int) ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_test_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_guest_tlb (struct kvm*) ; 

void kvmppc_check_need_tlb_flush(struct kvm *kvm, int pcpu,
				 struct kvm_nested_guest *nested)
{
	cpumask_t *need_tlb_flush;

	/*
	 * On POWER9, individual threads can come in here, but the
	 * TLB is shared between the 4 threads in a core, hence
	 * invalidating on one thread invalidates for all.
	 * Thus we make all 4 threads use the same bit.
	 */
	if (cpu_has_feature(CPU_FTR_ARCH_300))
		pcpu = cpu_first_thread_sibling(pcpu);

	if (nested)
		need_tlb_flush = &nested->need_tlb_flush;
	else
		need_tlb_flush = &kvm->arch.need_tlb_flush;

	if (cpumask_test_cpu(pcpu, need_tlb_flush)) {
		flush_guest_tlb(kvm);

		/* Clear the bit after the TLB flush */
		cpumask_clear_cpu(pcpu, need_tlb_flush);
	}
}