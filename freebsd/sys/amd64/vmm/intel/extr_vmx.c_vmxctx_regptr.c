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
struct vmxctx {int /*<<< orphan*/  guest_dr6; int /*<<< orphan*/  guest_dr3; int /*<<< orphan*/  guest_dr2; int /*<<< orphan*/  guest_dr1; int /*<<< orphan*/  guest_dr0; int /*<<< orphan*/  guest_cr2; int /*<<< orphan*/  guest_r15; int /*<<< orphan*/  guest_r14; int /*<<< orphan*/  guest_r13; int /*<<< orphan*/  guest_r12; int /*<<< orphan*/  guest_r11; int /*<<< orphan*/  guest_r10; int /*<<< orphan*/  guest_r9; int /*<<< orphan*/  guest_r8; int /*<<< orphan*/  guest_rbp; int /*<<< orphan*/  guest_rdi; int /*<<< orphan*/  guest_rsi; int /*<<< orphan*/  guest_rdx; int /*<<< orphan*/  guest_rcx; int /*<<< orphan*/  guest_rbx; int /*<<< orphan*/  guest_rax; } ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
#define  VM_REG_GUEST_CR2 148 
#define  VM_REG_GUEST_DR0 147 
#define  VM_REG_GUEST_DR1 146 
#define  VM_REG_GUEST_DR2 145 
#define  VM_REG_GUEST_DR3 144 
#define  VM_REG_GUEST_DR6 143 
#define  VM_REG_GUEST_R10 142 
#define  VM_REG_GUEST_R11 141 
#define  VM_REG_GUEST_R12 140 
#define  VM_REG_GUEST_R13 139 
#define  VM_REG_GUEST_R14 138 
#define  VM_REG_GUEST_R15 137 
#define  VM_REG_GUEST_R8 136 
#define  VM_REG_GUEST_R9 135 
#define  VM_REG_GUEST_RAX 134 
#define  VM_REG_GUEST_RBP 133 
#define  VM_REG_GUEST_RBX 132 
#define  VM_REG_GUEST_RCX 131 
#define  VM_REG_GUEST_RDI 130 
#define  VM_REG_GUEST_RDX 129 
#define  VM_REG_GUEST_RSI 128 

__attribute__((used)) static register_t *
vmxctx_regptr(struct vmxctx *vmxctx, int reg)
{

	switch (reg) {
	case VM_REG_GUEST_RAX:
		return (&vmxctx->guest_rax);
	case VM_REG_GUEST_RBX:
		return (&vmxctx->guest_rbx);
	case VM_REG_GUEST_RCX:
		return (&vmxctx->guest_rcx);
	case VM_REG_GUEST_RDX:
		return (&vmxctx->guest_rdx);
	case VM_REG_GUEST_RSI:
		return (&vmxctx->guest_rsi);
	case VM_REG_GUEST_RDI:
		return (&vmxctx->guest_rdi);
	case VM_REG_GUEST_RBP:
		return (&vmxctx->guest_rbp);
	case VM_REG_GUEST_R8:
		return (&vmxctx->guest_r8);
	case VM_REG_GUEST_R9:
		return (&vmxctx->guest_r9);
	case VM_REG_GUEST_R10:
		return (&vmxctx->guest_r10);
	case VM_REG_GUEST_R11:
		return (&vmxctx->guest_r11);
	case VM_REG_GUEST_R12:
		return (&vmxctx->guest_r12);
	case VM_REG_GUEST_R13:
		return (&vmxctx->guest_r13);
	case VM_REG_GUEST_R14:
		return (&vmxctx->guest_r14);
	case VM_REG_GUEST_R15:
		return (&vmxctx->guest_r15);
	case VM_REG_GUEST_CR2:
		return (&vmxctx->guest_cr2);
	case VM_REG_GUEST_DR0:
		return (&vmxctx->guest_dr0);
	case VM_REG_GUEST_DR1:
		return (&vmxctx->guest_dr1);
	case VM_REG_GUEST_DR2:
		return (&vmxctx->guest_dr2);
	case VM_REG_GUEST_DR3:
		return (&vmxctx->guest_dr3);
	case VM_REG_GUEST_DR6:
		return (&vmxctx->guest_dr6);
	default:
		break;
	}
	return (NULL);
}