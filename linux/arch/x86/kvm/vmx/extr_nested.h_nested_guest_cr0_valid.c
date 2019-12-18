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
typedef  int u64 ;
struct vmcs12 {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_4__ {int cr0_fixed0; int cr0_fixed1; int secondary_ctls_high; } ;
struct TYPE_5__ {TYPE_1__ msrs; } ;
struct TYPE_6__ {TYPE_2__ nested; } ;

/* Variables and functions */
 int SECONDARY_EXEC_UNRESTRICTED_GUEST ; 
 int X86_CR0_PE ; 
 int X86_CR0_PG ; 
 int fixed_bits_valid (unsigned long,int,int) ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 scalar_t__ nested_cpu_has2 (struct vmcs12*,int) ; 
 TYPE_3__* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static bool nested_guest_cr0_valid(struct kvm_vcpu *vcpu, unsigned long val)
{
	u64 fixed0 = to_vmx(vcpu)->nested.msrs.cr0_fixed0;
	u64 fixed1 = to_vmx(vcpu)->nested.msrs.cr0_fixed1;
	struct vmcs12 *vmcs12 = get_vmcs12(vcpu);

	if (to_vmx(vcpu)->nested.msrs.secondary_ctls_high &
		SECONDARY_EXEC_UNRESTRICTED_GUEST &&
	    nested_cpu_has2(vmcs12, SECONDARY_EXEC_UNRESTRICTED_GUEST))
		fixed0 &= ~(X86_CR0_PE | X86_CR0_PG);

	return fixed_bits_valid(val, fixed0, fixed1);
}