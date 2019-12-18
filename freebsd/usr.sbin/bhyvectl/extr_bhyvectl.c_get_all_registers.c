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
typedef  int /*<<< orphan*/  uint64_t ;
struct vmctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_REG_GUEST_CR0 ; 
 int /*<<< orphan*/  VM_REG_GUEST_CR2 ; 
 int /*<<< orphan*/  VM_REG_GUEST_CR3 ; 
 int /*<<< orphan*/  VM_REG_GUEST_CR4 ; 
 int /*<<< orphan*/  VM_REG_GUEST_DR0 ; 
 int /*<<< orphan*/  VM_REG_GUEST_DR1 ; 
 int /*<<< orphan*/  VM_REG_GUEST_DR2 ; 
 int /*<<< orphan*/  VM_REG_GUEST_DR3 ; 
 int /*<<< orphan*/  VM_REG_GUEST_DR6 ; 
 int /*<<< orphan*/  VM_REG_GUEST_DR7 ; 
 int /*<<< orphan*/  VM_REG_GUEST_EFER ; 
 int /*<<< orphan*/  VM_REG_GUEST_R10 ; 
 int /*<<< orphan*/  VM_REG_GUEST_R11 ; 
 int /*<<< orphan*/  VM_REG_GUEST_R12 ; 
 int /*<<< orphan*/  VM_REG_GUEST_R13 ; 
 int /*<<< orphan*/  VM_REG_GUEST_R14 ; 
 int /*<<< orphan*/  VM_REG_GUEST_R15 ; 
 int /*<<< orphan*/  VM_REG_GUEST_R8 ; 
 int /*<<< orphan*/  VM_REG_GUEST_R9 ; 
 int /*<<< orphan*/  VM_REG_GUEST_RAX ; 
 int /*<<< orphan*/  VM_REG_GUEST_RBP ; 
 int /*<<< orphan*/  VM_REG_GUEST_RBX ; 
 int /*<<< orphan*/  VM_REG_GUEST_RCX ; 
 int /*<<< orphan*/  VM_REG_GUEST_RDI ; 
 int /*<<< orphan*/  VM_REG_GUEST_RDX ; 
 int /*<<< orphan*/  VM_REG_GUEST_RFLAGS ; 
 int /*<<< orphan*/  VM_REG_GUEST_RIP ; 
 int /*<<< orphan*/  VM_REG_GUEST_RSI ; 
 int /*<<< orphan*/  VM_REG_GUEST_RSP ; 
 scalar_t__ get_all ; 
 scalar_t__ get_cr0 ; 
 scalar_t__ get_cr2 ; 
 scalar_t__ get_cr3 ; 
 scalar_t__ get_cr4 ; 
 scalar_t__ get_dr0 ; 
 scalar_t__ get_dr1 ; 
 scalar_t__ get_dr2 ; 
 scalar_t__ get_dr3 ; 
 scalar_t__ get_dr6 ; 
 scalar_t__ get_dr7 ; 
 scalar_t__ get_efer ; 
 scalar_t__ get_r10 ; 
 scalar_t__ get_r11 ; 
 scalar_t__ get_r12 ; 
 scalar_t__ get_r13 ; 
 scalar_t__ get_r14 ; 
 scalar_t__ get_r15 ; 
 scalar_t__ get_r8 ; 
 scalar_t__ get_r9 ; 
 scalar_t__ get_rax ; 
 scalar_t__ get_rbp ; 
 scalar_t__ get_rbx ; 
 scalar_t__ get_rcx ; 
 scalar_t__ get_rdi ; 
 scalar_t__ get_rdx ; 
 scalar_t__ get_rflags ; 
 scalar_t__ get_rip ; 
 scalar_t__ get_rsi ; 
 scalar_t__ get_rsp ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ) ; 
 int vm_get_register (struct vmctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_all_registers(struct vmctx *ctx, int vcpu)
{
	uint64_t cr0, cr2, cr3, cr4, dr0, dr1, dr2, dr3, dr6, dr7;
	uint64_t rsp, rip, rflags, efer;
	uint64_t rax, rbx, rcx, rdx, rsi, rdi, rbp;
	uint64_t r8, r9, r10, r11, r12, r13, r14, r15;
	int error = 0;

	if (!error && (get_efer || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_EFER, &efer);
		if (error == 0)
			printf("efer[%d]\t\t0x%016lx\n", vcpu, efer);
	}

	if (!error && (get_cr0 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_CR0, &cr0);
		if (error == 0)
			printf("cr0[%d]\t\t0x%016lx\n", vcpu, cr0);
	}

	if (!error && (get_cr2 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_CR2, &cr2);
		if (error == 0)
			printf("cr2[%d]\t\t0x%016lx\n", vcpu, cr2);
	}

	if (!error && (get_cr3 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_CR3, &cr3);
		if (error == 0)
			printf("cr3[%d]\t\t0x%016lx\n", vcpu, cr3);
	}

	if (!error && (get_cr4 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_CR4, &cr4);
		if (error == 0)
			printf("cr4[%d]\t\t0x%016lx\n", vcpu, cr4);
	}

	if (!error && (get_dr0 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_DR0, &dr0);
		if (error == 0)
			printf("dr0[%d]\t\t0x%016lx\n", vcpu, dr0);
	}

	if (!error && (get_dr1 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_DR1, &dr1);
		if (error == 0)
			printf("dr1[%d]\t\t0x%016lx\n", vcpu, dr1);
	}

	if (!error && (get_dr2 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_DR2, &dr2);
		if (error == 0)
			printf("dr2[%d]\t\t0x%016lx\n", vcpu, dr2);
	}

	if (!error && (get_dr3 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_DR3, &dr3);
		if (error == 0)
			printf("dr3[%d]\t\t0x%016lx\n", vcpu, dr3);
	}

	if (!error && (get_dr6 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_DR6, &dr6);
		if (error == 0)
			printf("dr6[%d]\t\t0x%016lx\n", vcpu, dr6);
	}

	if (!error && (get_dr7 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_DR7, &dr7);
		if (error == 0)
			printf("dr7[%d]\t\t0x%016lx\n", vcpu, dr7);
	}

	if (!error && (get_rsp || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_RSP, &rsp);
		if (error == 0)
			printf("rsp[%d]\t\t0x%016lx\n", vcpu, rsp);
	}

	if (!error && (get_rip || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_RIP, &rip);
		if (error == 0)
			printf("rip[%d]\t\t0x%016lx\n", vcpu, rip);
	}

	if (!error && (get_rax || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_RAX, &rax);
		if (error == 0)
			printf("rax[%d]\t\t0x%016lx\n", vcpu, rax);
	}

	if (!error && (get_rbx || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_RBX, &rbx);
		if (error == 0)
			printf("rbx[%d]\t\t0x%016lx\n", vcpu, rbx);
	}

	if (!error && (get_rcx || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_RCX, &rcx);
		if (error == 0)
			printf("rcx[%d]\t\t0x%016lx\n", vcpu, rcx);
	}

	if (!error && (get_rdx || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_RDX, &rdx);
		if (error == 0)
			printf("rdx[%d]\t\t0x%016lx\n", vcpu, rdx);
	}

	if (!error && (get_rsi || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_RSI, &rsi);
		if (error == 0)
			printf("rsi[%d]\t\t0x%016lx\n", vcpu, rsi);
	}

	if (!error && (get_rdi || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_RDI, &rdi);
		if (error == 0)
			printf("rdi[%d]\t\t0x%016lx\n", vcpu, rdi);
	}

	if (!error && (get_rbp || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_RBP, &rbp);
		if (error == 0)
			printf("rbp[%d]\t\t0x%016lx\n", vcpu, rbp);
	}

	if (!error && (get_r8 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_R8, &r8);
		if (error == 0)
			printf("r8[%d]\t\t0x%016lx\n", vcpu, r8);
	}

	if (!error && (get_r9 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_R9, &r9);
		if (error == 0)
			printf("r9[%d]\t\t0x%016lx\n", vcpu, r9);
	}

	if (!error && (get_r10 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_R10, &r10);
		if (error == 0)
			printf("r10[%d]\t\t0x%016lx\n", vcpu, r10);
	}

	if (!error && (get_r11 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_R11, &r11);
		if (error == 0)
			printf("r11[%d]\t\t0x%016lx\n", vcpu, r11);
	}

	if (!error && (get_r12 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_R12, &r12);
		if (error == 0)
			printf("r12[%d]\t\t0x%016lx\n", vcpu, r12);
	}

	if (!error && (get_r13 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_R13, &r13);
		if (error == 0)
			printf("r13[%d]\t\t0x%016lx\n", vcpu, r13);
	}

	if (!error && (get_r14 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_R14, &r14);
		if (error == 0)
			printf("r14[%d]\t\t0x%016lx\n", vcpu, r14);
	}

	if (!error && (get_r15 || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_R15, &r15);
		if (error == 0)
			printf("r15[%d]\t\t0x%016lx\n", vcpu, r15);
	}

	if (!error && (get_rflags || get_all)) {
		error = vm_get_register(ctx, vcpu, VM_REG_GUEST_RFLAGS,
					&rflags);
		if (error == 0)
			printf("rflags[%d]\t0x%016lx\n", vcpu, rflags);
	}

	return (error);
}