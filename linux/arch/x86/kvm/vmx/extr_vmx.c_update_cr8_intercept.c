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
struct vmcs12 {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_BASED_TPR_SHADOW ; 
 int /*<<< orphan*/  TPR_THRESHOLD ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 scalar_t__ nested_cpu_has (struct vmcs12*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void update_cr8_intercept(struct kvm_vcpu *vcpu, int tpr, int irr)
{
	struct vmcs12 *vmcs12 = get_vmcs12(vcpu);

	if (is_guest_mode(vcpu) &&
		nested_cpu_has(vmcs12, CPU_BASED_TPR_SHADOW))
		return;

	if (irr == -1 || tpr < irr) {
		vmcs_write32(TPR_THRESHOLD, 0);
		return;
	}

	vmcs_write32(TPR_THRESHOLD, irr);
}