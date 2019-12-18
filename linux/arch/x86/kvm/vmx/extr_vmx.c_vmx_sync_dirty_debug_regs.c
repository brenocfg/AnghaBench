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
struct TYPE_2__ {int /*<<< orphan*/  switch_db_regs; int /*<<< orphan*/  dr7; int /*<<< orphan*/  dr6; int /*<<< orphan*/ * db; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_BASED_MOV_DR_EXITING ; 
 int /*<<< orphan*/  GUEST_DR7 ; 
 int /*<<< orphan*/  KVM_DEBUGREG_WONT_EXIT ; 
 int /*<<< orphan*/  exec_controls_setbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_debugreg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmx_sync_dirty_debug_regs(struct kvm_vcpu *vcpu)
{
	get_debugreg(vcpu->arch.db[0], 0);
	get_debugreg(vcpu->arch.db[1], 1);
	get_debugreg(vcpu->arch.db[2], 2);
	get_debugreg(vcpu->arch.db[3], 3);
	get_debugreg(vcpu->arch.dr6, 6);
	vcpu->arch.dr7 = vmcs_readl(GUEST_DR7);

	vcpu->arch.switch_db_regs &= ~KVM_DEBUGREG_WONT_EXIT;
	exec_controls_setbit(to_vmx(vcpu), CPU_BASED_MOV_DR_EXITING);
}