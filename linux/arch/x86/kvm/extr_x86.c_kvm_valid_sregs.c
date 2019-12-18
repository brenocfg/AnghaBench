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
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {scalar_t__ l; } ;
struct kvm_sregs {int efer; int cr0; int cr4; TYPE_1__ cs; } ;

/* Variables and functions */
 int EFER_LMA ; 
 int EFER_LME ; 
 int EINVAL ; 
 int X86_CR0_PG ; 
 int X86_CR4_PAE ; 
 int kvm_valid_cr4 (struct kvm_vcpu*,int) ; 

__attribute__((used)) static int kvm_valid_sregs(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
{
	if ((sregs->efer & EFER_LME) && (sregs->cr0 & X86_CR0_PG)) {
		/*
		 * When EFER.LME and CR0.PG are set, the processor is in
		 * 64-bit mode (though maybe in a 32-bit code segment).
		 * CR4.PAE and EFER.LMA must be set.
		 */
		if (!(sregs->cr4 & X86_CR4_PAE)
		    || !(sregs->efer & EFER_LMA))
			return -EINVAL;
	} else {
		/*
		 * Not in 64-bit mode: EFER.LMA is clear and the code
		 * segment cannot be 64-bit.
		 */
		if (sregs->efer & EFER_LMA || sregs->cs.l)
			return -EINVAL;
	}

	return kvm_valid_cr4(vcpu, sregs->cr4);
}