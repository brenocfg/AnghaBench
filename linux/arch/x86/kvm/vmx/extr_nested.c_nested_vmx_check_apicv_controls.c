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
struct vmcs12 {int posted_intr_nv; int posted_intr_desc_addr; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ CC (int) ; 
 int /*<<< orphan*/  CPU_BASED_TPR_SHADOW ; 
 int EINVAL ; 
 int /*<<< orphan*/  SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES ; 
 int cpuid_maxphyaddr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_cpu_has (struct vmcs12*,int /*<<< orphan*/ ) ; 
 scalar_t__ nested_cpu_has2 (struct vmcs12*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_cpu_has_apic_reg_virt (struct vmcs12*) ; 
 scalar_t__ nested_cpu_has_posted_intr (struct vmcs12*) ; 
 scalar_t__ nested_cpu_has_vid (struct vmcs12*) ; 
 scalar_t__ nested_cpu_has_virt_x2apic_mode (struct vmcs12*) ; 
 int /*<<< orphan*/  nested_exit_intr_ack_set (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_exit_on_intr (struct kvm_vcpu*) ; 

__attribute__((used)) static int nested_vmx_check_apicv_controls(struct kvm_vcpu *vcpu,
					   struct vmcs12 *vmcs12)
{
	if (!nested_cpu_has_virt_x2apic_mode(vmcs12) &&
	    !nested_cpu_has_apic_reg_virt(vmcs12) &&
	    !nested_cpu_has_vid(vmcs12) &&
	    !nested_cpu_has_posted_intr(vmcs12))
		return 0;

	/*
	 * If virtualize x2apic mode is enabled,
	 * virtualize apic access must be disabled.
	 */
	if (CC(nested_cpu_has_virt_x2apic_mode(vmcs12) &&
	       nested_cpu_has2(vmcs12, SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES)))
		return -EINVAL;

	/*
	 * If virtual interrupt delivery is enabled,
	 * we must exit on external interrupts.
	 */
	if (CC(nested_cpu_has_vid(vmcs12) && !nested_exit_on_intr(vcpu)))
		return -EINVAL;

	/*
	 * bits 15:8 should be zero in posted_intr_nv,
	 * the descriptor address has been already checked
	 * in nested_get_vmcs12_pages.
	 *
	 * bits 5:0 of posted_intr_desc_addr should be zero.
	 */
	if (nested_cpu_has_posted_intr(vmcs12) &&
	   (CC(!nested_cpu_has_vid(vmcs12)) ||
	    CC(!nested_exit_intr_ack_set(vcpu)) ||
	    CC((vmcs12->posted_intr_nv & 0xff00)) ||
	    CC((vmcs12->posted_intr_desc_addr & 0x3f)) ||
	    CC((vmcs12->posted_intr_desc_addr >> cpuid_maxphyaddr(vcpu)))))
		return -EINVAL;

	/* tpr shadow is needed by all apicv features. */
	if (CC(!nested_cpu_has(vmcs12, CPU_BASED_TPR_SHADOW)))
		return -EINVAL;

	return 0;
}