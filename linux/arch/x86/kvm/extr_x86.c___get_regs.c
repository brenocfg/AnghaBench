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
struct TYPE_2__ {int emulate_regs_need_sync_to_vcpu; int /*<<< orphan*/  emulate_ctxt; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_regs {int /*<<< orphan*/  rflags; int /*<<< orphan*/  rip; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  rbp; int /*<<< orphan*/  rsp; int /*<<< orphan*/  rdi; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rax; } ;

/* Variables and functions */
 int /*<<< orphan*/  emulator_writeback_register_cache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_get_rflags (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_r10_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_r11_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_r12_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_r13_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_r14_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_r15_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_r8_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_r9_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rax_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rbp_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rbx_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rcx_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rdi_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rdx_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rip_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rsi_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rsp_read (struct kvm_vcpu*) ; 

__attribute__((used)) static void __get_regs(struct kvm_vcpu *vcpu, struct kvm_regs *regs)
{
	if (vcpu->arch.emulate_regs_need_sync_to_vcpu) {
		/*
		 * We are here if userspace calls get_regs() in the middle of
		 * instruction emulation. Registers state needs to be copied
		 * back from emulation context to vcpu. Userspace shouldn't do
		 * that usually, but some bad designed PV devices (vmware
		 * backdoor interface) need this to work
		 */
		emulator_writeback_register_cache(&vcpu->arch.emulate_ctxt);
		vcpu->arch.emulate_regs_need_sync_to_vcpu = false;
	}
	regs->rax = kvm_rax_read(vcpu);
	regs->rbx = kvm_rbx_read(vcpu);
	regs->rcx = kvm_rcx_read(vcpu);
	regs->rdx = kvm_rdx_read(vcpu);
	regs->rsi = kvm_rsi_read(vcpu);
	regs->rdi = kvm_rdi_read(vcpu);
	regs->rsp = kvm_rsp_read(vcpu);
	regs->rbp = kvm_rbp_read(vcpu);
#ifdef CONFIG_X86_64
	regs->r8 = kvm_r8_read(vcpu);
	regs->r9 = kvm_r9_read(vcpu);
	regs->r10 = kvm_r10_read(vcpu);
	regs->r11 = kvm_r11_read(vcpu);
	regs->r12 = kvm_r12_read(vcpu);
	regs->r13 = kvm_r13_read(vcpu);
	regs->r14 = kvm_r14_read(vcpu);
	regs->r15 = kvm_r15_read(vcpu);
#endif

	regs->rip = kvm_rip_read(vcpu);
	regs->rflags = kvm_get_rflags(vcpu);
}