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
typedef  unsigned int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ kvm_get_msr (struct kvm_vcpu*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  kvm_inject_gp (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_rax_write (struct kvm_vcpu*,unsigned int) ; 
 int /*<<< orphan*/  kvm_rcx_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rdx_write (struct kvm_vcpu*,unsigned int) ; 
 int kvm_skip_emulated_instruction (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_msr_read (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  trace_kvm_msr_read_ex (int /*<<< orphan*/ ) ; 

int kvm_emulate_rdmsr(struct kvm_vcpu *vcpu)
{
	u32 ecx = kvm_rcx_read(vcpu);
	u64 data;

	if (kvm_get_msr(vcpu, ecx, &data)) {
		trace_kvm_msr_read_ex(ecx);
		kvm_inject_gp(vcpu, 0);
		return 1;
	}

	trace_kvm_msr_read(ecx, data);

	kvm_rax_write(vcpu, data & -1u);
	kvm_rdx_write(vcpu, (data >> 32) & -1u);
	return kvm_skip_emulated_instruction(vcpu);
}