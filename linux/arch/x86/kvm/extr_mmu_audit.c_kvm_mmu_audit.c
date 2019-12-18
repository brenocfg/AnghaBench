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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __kvm_mmu_audit (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  mmu_audit_key ; 
 scalar_t__ static_key_false (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void kvm_mmu_audit(struct kvm_vcpu *vcpu, int point)
{
	if (static_key_false((&mmu_audit_key)))
		__kvm_mmu_audit(vcpu, point);
}