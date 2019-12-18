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
struct TYPE_2__ {scalar_t__ mmio_gfn; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  scalar_t__ gpa_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ vcpu_match_mmio_gen (struct kvm_vcpu*) ; 

__attribute__((used)) static inline bool vcpu_match_mmio_gpa(struct kvm_vcpu *vcpu, gpa_t gpa)
{
	if (vcpu_match_mmio_gen(vcpu) && vcpu->arch.mmio_gfn &&
	      vcpu->arch.mmio_gfn == gpa >> PAGE_SHIFT)
		return true;

	return false;
}