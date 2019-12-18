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
struct TYPE_2__ {unsigned int host_cp0_guestctl0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int MIPS_GCTL0_GEXC ; 
 unsigned int MIPS_GCTL0_GEXC_GPA ; 
 unsigned int MIPS_GCTL0_GEXC_GVA ; 
 unsigned int MIPS_GCTL0_GEXC_SHIFT ; 
 scalar_t__ WARN (int,char*,unsigned int) ; 
 int kvm_vz_gva_to_gpa (struct kvm_vcpu*,unsigned long,unsigned long*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int kvm_vz_badvaddr_to_gpa(struct kvm_vcpu *vcpu, unsigned long badvaddr,
				  unsigned long *gpa)
{
	unsigned int gexccode = (vcpu->arch.host_cp0_guestctl0 &
				 MIPS_GCTL0_GEXC) >> MIPS_GCTL0_GEXC_SHIFT;

	/* If BadVAddr is GPA, then all is well in the world */
	if (likely(gexccode == MIPS_GCTL0_GEXC_GPA)) {
		*gpa = badvaddr;
		return 0;
	}

	/* Otherwise we'd expect it to be GVA ... */
	if (WARN(gexccode != MIPS_GCTL0_GEXC_GVA,
		 "Unexpected gexccode %#x\n", gexccode))
		return -EINVAL;

	/* ... and we need to perform the GVA->GPA translation in software */
	return kvm_vz_gva_to_gpa(vcpu, badvaddr, gpa);
}