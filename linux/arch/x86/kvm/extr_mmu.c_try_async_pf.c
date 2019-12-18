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
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct kvm_memory_slot {int dummy; } ;
typedef  int /*<<< orphan*/  kvm_pfn_t ;
typedef  int /*<<< orphan*/  gva_t ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_PFN_NOSLOT ; 
 int /*<<< orphan*/  KVM_REQ_APF_HALT ; 
 int /*<<< orphan*/  __gfn_to_pfn_memslot (struct kvm_memory_slot*,int /*<<< orphan*/ ,int,int*,int,int*) ; 
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 scalar_t__ kvm_arch_setup_async_pf (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_can_do_async_pf (struct kvm_vcpu*) ; 
 scalar_t__ kvm_find_async_pf_gfn (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_is_visible_gfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 struct kvm_memory_slot* kvm_vcpu_gfn_to_memslot (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_async_pf_doublefault (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_try_async_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool try_async_pf(struct kvm_vcpu *vcpu, bool prefault, gfn_t gfn,
			 gva_t gva, kvm_pfn_t *pfn, bool write, bool *writable)
{
	struct kvm_memory_slot *slot;
	bool async;

	/*
	 * Don't expose private memslots to L2.
	 */
	if (is_guest_mode(vcpu) && !kvm_is_visible_gfn(vcpu->kvm, gfn)) {
		*pfn = KVM_PFN_NOSLOT;
		return false;
	}

	slot = kvm_vcpu_gfn_to_memslot(vcpu, gfn);
	async = false;
	*pfn = __gfn_to_pfn_memslot(slot, gfn, false, &async, write, writable);
	if (!async)
		return false; /* *pfn has correct page already */

	if (!prefault && kvm_can_do_async_pf(vcpu)) {
		trace_kvm_try_async_get_page(gva, gfn);
		if (kvm_find_async_pf_gfn(vcpu, gfn)) {
			trace_kvm_async_pf_doublefault(gva, gfn);
			kvm_make_request(KVM_REQ_APF_HALT, vcpu);
			return true;
		} else if (kvm_arch_setup_async_pf(vcpu, gva, gfn))
			return true;
	}

	*pfn = __gfn_to_pfn_memslot(slot, gfn, false, NULL, write, writable);
	return false;
}