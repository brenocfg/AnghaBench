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
struct TYPE_2__ {unsigned long mmio_gva; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 scalar_t__ vcpu_match_mmio_gen (struct kvm_vcpu*) ; 

__attribute__((used)) static inline bool vcpu_match_mmio_gva(struct kvm_vcpu *vcpu, unsigned long gva)
{
	if (vcpu_match_mmio_gen(vcpu) && vcpu->arch.mmio_gva &&
	      vcpu->arch.mmio_gva == (gva & PAGE_MASK))
		return true;

	return false;
}