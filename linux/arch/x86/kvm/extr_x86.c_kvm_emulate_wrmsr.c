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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_inject_gp (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_rcx_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_read_edx_eax (struct kvm_vcpu*) ; 
 scalar_t__ kvm_set_msr (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kvm_skip_emulated_instruction (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_msr_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_msr_write_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int kvm_emulate_wrmsr(struct kvm_vcpu *vcpu)
{
	u32 ecx = kvm_rcx_read(vcpu);
	u64 data = kvm_read_edx_eax(vcpu);

	if (kvm_set_msr(vcpu, ecx, data)) {
		trace_kvm_msr_write_ex(ecx, data);
		kvm_inject_gp(vcpu, 0);
		return 1;
	}

	trace_kvm_msr_write(ecx, data);
	return kvm_skip_emulated_instruction(vcpu);
}