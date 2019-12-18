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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ mmu_is_nested (struct kvm_vcpu*) ; 
 int vcpu_match_mmio_gpa (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int vcpu_match_mmio_gva (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mmio_info_in_cache(struct kvm_vcpu *vcpu, u64 addr, bool direct)
{
	/*
	 * A nested guest cannot use the MMIO cache if it is using nested
	 * page tables, because cr2 is a nGPA while the cache stores GPAs.
	 */
	if (mmu_is_nested(vcpu))
		return false;

	if (direct)
		return vcpu_match_mmio_gpa(vcpu, addr);

	return vcpu_match_mmio_gva(vcpu, addr);
}