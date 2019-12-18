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
struct TYPE_2__ {size_t nested_vcpu_id; int prev_cpu; struct kvm_nested_guest* nested; } ;
struct kvm_vcpu {TYPE_1__ arch; struct kvm* kvm; } ;
struct kvm_nested_guest {int* prev_cpu; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 scalar_t__ cpu_first_thread_sibling (int) ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_flush_cpu (struct kvm*,int,struct kvm_vcpu*) ; 

__attribute__((used)) static void kvmppc_prepare_radix_vcpu(struct kvm_vcpu *vcpu, int pcpu)
{
	struct kvm_nested_guest *nested = vcpu->arch.nested;
	struct kvm *kvm = vcpu->kvm;
	int prev_cpu;

	if (!cpu_has_feature(CPU_FTR_HVMODE))
		return;

	if (nested)
		prev_cpu = nested->prev_cpu[vcpu->arch.nested_vcpu_id];
	else
		prev_cpu = vcpu->arch.prev_cpu;

	/*
	 * With radix, the guest can do TLB invalidations itself,
	 * and it could choose to use the local form (tlbiel) if
	 * it is invalidating a translation that has only ever been
	 * used on one vcpu.  However, that doesn't mean it has
	 * only ever been used on one physical cpu, since vcpus
	 * can move around between pcpus.  To cope with this, when
	 * a vcpu moves from one pcpu to another, we need to tell
	 * any vcpus running on the same core as this vcpu previously
	 * ran to flush the TLB.  The TLB is shared between threads,
	 * so we use a single bit in .need_tlb_flush for all 4 threads.
	 */
	if (prev_cpu != pcpu) {
		if (prev_cpu >= 0 &&
		    cpu_first_thread_sibling(prev_cpu) !=
		    cpu_first_thread_sibling(pcpu))
			radix_flush_cpu(kvm, prev_cpu, vcpu);
		if (nested)
			nested->prev_cpu[vcpu->arch.nested_vcpu_id] = pcpu;
		else
			vcpu->arch.prev_cpu = pcpu;
	}
}