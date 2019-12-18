#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* shared; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_2__ arch; } ;
struct kvm_book3e_206_tlb_entry {int dummy; } ;
typedef  int gpa_t ;
struct TYPE_3__ {int msr; } ;

/* Variables and functions */
 int MSR_IS ; 
 int PAGE_SHIFT ; 
 int get_tlb_raddr (struct kvm_book3e_206_tlb_entry const*) ; 
 int get_tlb_ts (struct kvm_book3e_206_tlb_entry const*) ; 
 int /*<<< orphan*/  get_tlb_v (struct kvm_book3e_206_tlb_entry const*) ; 
 int /*<<< orphan*/  gfn_to_memslot (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int tlbe_is_host_safe(const struct kvm_vcpu *vcpu,
			const struct kvm_book3e_206_tlb_entry *tlbe)
{
	gpa_t gpa;

	if (!get_tlb_v(tlbe))
		return 0;

#ifndef CONFIG_KVM_BOOKE_HV
	/* Does it match current guest AS? */
	/* XXX what about IS != DS? */
	if (get_tlb_ts(tlbe) != !!(vcpu->arch.shared->msr & MSR_IS))
		return 0;
#endif

	gpa = get_tlb_raddr(tlbe);
	if (!gfn_to_memslot(vcpu->kvm, gpa >> PAGE_SHIFT))
		/* Mapping is not for RAM. */
		return 0;

	return 1;
}