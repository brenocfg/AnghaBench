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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct msr_data {int index; int host_initiated; int /*<<< orphan*/  data; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int (* set_msr ) (struct kvm_vcpu*,struct msr_data*) ;} ;

/* Variables and functions */
#define  MSR_CSTAR 134 
#define  MSR_FS_BASE 133 
#define  MSR_GS_BASE 132 
#define  MSR_IA32_SYSENTER_EIP 131 
#define  MSR_IA32_SYSENTER_ESP 130 
#define  MSR_KERNEL_GS_BASE 129 
#define  MSR_LSTAR 128 
 int /*<<< orphan*/  get_canonical (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_noncanonical_address (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 TYPE_1__* kvm_x86_ops ; 
 int stub1 (struct kvm_vcpu*,struct msr_data*) ; 
 int /*<<< orphan*/  vcpu_virt_addr_bits (struct kvm_vcpu*) ; 

__attribute__((used)) static int __kvm_set_msr(struct kvm_vcpu *vcpu, u32 index, u64 data,
			 bool host_initiated)
{
	struct msr_data msr;

	switch (index) {
	case MSR_FS_BASE:
	case MSR_GS_BASE:
	case MSR_KERNEL_GS_BASE:
	case MSR_CSTAR:
	case MSR_LSTAR:
		if (is_noncanonical_address(data, vcpu))
			return 1;
		break;
	case MSR_IA32_SYSENTER_EIP:
	case MSR_IA32_SYSENTER_ESP:
		/*
		 * IA32_SYSENTER_ESP and IA32_SYSENTER_EIP cause #GP if
		 * non-canonical address is written on Intel but not on
		 * AMD (which ignores the top 32-bits, because it does
		 * not implement 64-bit SYSENTER).
		 *
		 * 64-bit code should hence be able to write a non-canonical
		 * value on AMD.  Making the address canonical ensures that
		 * vmentry does not fail on Intel after writing a non-canonical
		 * value, and that something deterministic happens if the guest
		 * invokes 64-bit SYSENTER.
		 */
		data = get_canonical(data, vcpu_virt_addr_bits(vcpu));
	}

	msr.data = data;
	msr.index = index;
	msr.host_initiated = host_initiated;

	return kvm_x86_ops->set_msr(vcpu, &msr);
}