#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ vmxon; } ;
struct TYPE_4__ {scalar_t__ vm86_active; } ;
struct vcpu_vmx {TYPE_2__ nested; TYPE_1__ rmode; } ;
struct TYPE_6__ {unsigned long cr4; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR4_READ_SHADOW ; 
 int /*<<< orphan*/  GUEST_CR4 ; 
 unsigned long KVM_PMODE_VM_CR4_ALWAYS_ON ; 
 unsigned long KVM_RMODE_VM_CR4_ALWAYS_ON ; 
 unsigned long KVM_VM_CR4_ALWAYS_ON_UNRESTRICTED_GUEST ; 
 int /*<<< orphan*/  SECONDARY_EXEC_DESC ; 
 unsigned long X86_CR4_MCE ; 
 unsigned long X86_CR4_PAE ; 
 unsigned long X86_CR4_PKE ; 
 unsigned long X86_CR4_PSE ; 
 unsigned long X86_CR4_SMAP ; 
 unsigned long X86_CR4_SMEP ; 
 unsigned long X86_CR4_UMIP ; 
 unsigned long X86_CR4_VMXE ; 
 int /*<<< orphan*/  X86_FEATURE_UMIP ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 unsigned long cr4_read_shadow () ; 
 scalar_t__ enable_ept ; 
 scalar_t__ enable_unrestricted_guest ; 
 int /*<<< orphan*/  get_vmcs12 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_guest_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_paging (struct kvm_vcpu*) ; 
 scalar_t__ is_smm (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_cpu_has2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_cr4_valid (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  nested_vmx_allowed (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  secondary_exec_controls_clearbit (struct vcpu_vmx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secondary_exec_controls_setbit (struct vcpu_vmx*,int /*<<< orphan*/ ) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_writel (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ vmx_umip_emulated () ; 

int vmx_set_cr4(struct kvm_vcpu *vcpu, unsigned long cr4)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	/*
	 * Pass through host's Machine Check Enable value to hw_cr4, which
	 * is in force while we are in guest mode.  Do not let guests control
	 * this bit, even if host CR4.MCE == 0.
	 */
	unsigned long hw_cr4;

	hw_cr4 = (cr4_read_shadow() & X86_CR4_MCE) | (cr4 & ~X86_CR4_MCE);
	if (enable_unrestricted_guest)
		hw_cr4 |= KVM_VM_CR4_ALWAYS_ON_UNRESTRICTED_GUEST;
	else if (vmx->rmode.vm86_active)
		hw_cr4 |= KVM_RMODE_VM_CR4_ALWAYS_ON;
	else
		hw_cr4 |= KVM_PMODE_VM_CR4_ALWAYS_ON;

	if (!boot_cpu_has(X86_FEATURE_UMIP) && vmx_umip_emulated()) {
		if (cr4 & X86_CR4_UMIP) {
			secondary_exec_controls_setbit(vmx, SECONDARY_EXEC_DESC);
			hw_cr4 &= ~X86_CR4_UMIP;
		} else if (!is_guest_mode(vcpu) ||
			!nested_cpu_has2(get_vmcs12(vcpu), SECONDARY_EXEC_DESC)) {
			secondary_exec_controls_clearbit(vmx, SECONDARY_EXEC_DESC);
		}
	}

	if (cr4 & X86_CR4_VMXE) {
		/*
		 * To use VMXON (and later other VMX instructions), a guest
		 * must first be able to turn on cr4.VMXE (see handle_vmon()).
		 * So basically the check on whether to allow nested VMX
		 * is here.  We operate under the default treatment of SMM,
		 * so VMX cannot be enabled under SMM.
		 */
		if (!nested_vmx_allowed(vcpu) || is_smm(vcpu))
			return 1;
	}

	if (vmx->nested.vmxon && !nested_cr4_valid(vcpu, cr4))
		return 1;

	vcpu->arch.cr4 = cr4;

	if (!enable_unrestricted_guest) {
		if (enable_ept) {
			if (!is_paging(vcpu)) {
				hw_cr4 &= ~X86_CR4_PAE;
				hw_cr4 |= X86_CR4_PSE;
			} else if (!(cr4 & X86_CR4_PAE)) {
				hw_cr4 &= ~X86_CR4_PAE;
			}
		}

		/*
		 * SMEP/SMAP/PKU is disabled if CPU is in non-paging mode in
		 * hardware.  To emulate this behavior, SMEP/SMAP/PKU needs
		 * to be manually disabled when guest switches to non-paging
		 * mode.
		 *
		 * If !enable_unrestricted_guest, the CPU is always running
		 * with CR0.PG=1 and CR4 needs to be modified.
		 * If enable_unrestricted_guest, the CPU automatically
		 * disables SMEP/SMAP/PKU when the guest sets CR0.PG=0.
		 */
		if (!is_paging(vcpu))
			hw_cr4 &= ~(X86_CR4_SMEP | X86_CR4_SMAP | X86_CR4_PKE);
	}

	vmcs_writel(CR4_READ_SHADOW, cr4);
	vmcs_writel(GUEST_CR4, hw_cr4);
	return 0;
}