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
struct x86_exception {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gva_t ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_QUALIFICATION ; 
 int /*<<< orphan*/  VMX_INSTRUCTION_INFO ; 
 scalar_t__ get_vmx_mem_address (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_inject_page_fault (struct kvm_vcpu*,struct x86_exception*) ; 
 scalar_t__ kvm_read_guest_virt (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct x86_exception*) ; 
 int /*<<< orphan*/  vmcs_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nested_vmx_get_vmptr(struct kvm_vcpu *vcpu, gpa_t *vmpointer)
{
	gva_t gva;
	struct x86_exception e;

	if (get_vmx_mem_address(vcpu, vmcs_readl(EXIT_QUALIFICATION),
				vmcs_read32(VMX_INSTRUCTION_INFO), false,
				sizeof(*vmpointer), &gva))
		return 1;

	if (kvm_read_guest_virt(vcpu, gva, vmpointer, sizeof(*vmpointer), &e)) {
		kvm_inject_page_fault(vcpu, &e);
		return 1;
	}

	return 0;
}