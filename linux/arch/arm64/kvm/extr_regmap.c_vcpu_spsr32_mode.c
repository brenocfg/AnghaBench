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
 int /*<<< orphan*/  BUG () ; 
 int KVM_SPSR_ABT ; 
 int KVM_SPSR_FIQ ; 
 int KVM_SPSR_IRQ ; 
 int KVM_SPSR_SVC ; 
 int KVM_SPSR_UND ; 
#define  PSR_AA32_MODE_ABT 132 
#define  PSR_AA32_MODE_FIQ 131 
#define  PSR_AA32_MODE_IRQ 130 
 unsigned long PSR_AA32_MODE_MASK ; 
#define  PSR_AA32_MODE_SVC 129 
#define  PSR_AA32_MODE_UND 128 
 unsigned long* vcpu_cpsr (struct kvm_vcpu const*) ; 

__attribute__((used)) static int vcpu_spsr32_mode(const struct kvm_vcpu *vcpu)
{
	unsigned long mode = *vcpu_cpsr(vcpu) & PSR_AA32_MODE_MASK;
	switch (mode) {
	case PSR_AA32_MODE_SVC: return KVM_SPSR_SVC;
	case PSR_AA32_MODE_ABT: return KVM_SPSR_ABT;
	case PSR_AA32_MODE_UND: return KVM_SPSR_UND;
	case PSR_AA32_MODE_IRQ: return KVM_SPSR_IRQ;
	case PSR_AA32_MODE_FIQ: return KVM_SPSR_FIQ;
	default: BUG();
	}
}