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
struct svm_regctx {int /*<<< orphan*/  sctx_dr3; int /*<<< orphan*/  sctx_dr2; int /*<<< orphan*/  sctx_dr1; int /*<<< orphan*/  sctx_dr0; int /*<<< orphan*/  sctx_r15; int /*<<< orphan*/  sctx_r14; int /*<<< orphan*/  sctx_r13; int /*<<< orphan*/  sctx_r12; int /*<<< orphan*/  sctx_r11; int /*<<< orphan*/  sctx_r10; int /*<<< orphan*/  sctx_r9; int /*<<< orphan*/  sctx_r8; int /*<<< orphan*/  sctx_rbp; int /*<<< orphan*/  sctx_rsi; int /*<<< orphan*/  sctx_rdi; int /*<<< orphan*/  sctx_rdx; int /*<<< orphan*/  sctx_rcx; int /*<<< orphan*/  sctx_rbx; } ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
#define  VM_REG_GUEST_DR0 145 
#define  VM_REG_GUEST_DR1 144 
#define  VM_REG_GUEST_DR2 143 
#define  VM_REG_GUEST_DR3 142 
#define  VM_REG_GUEST_R10 141 
#define  VM_REG_GUEST_R11 140 
#define  VM_REG_GUEST_R12 139 
#define  VM_REG_GUEST_R13 138 
#define  VM_REG_GUEST_R14 137 
#define  VM_REG_GUEST_R15 136 
#define  VM_REG_GUEST_R8 135 
#define  VM_REG_GUEST_R9 134 
#define  VM_REG_GUEST_RBP 133 
#define  VM_REG_GUEST_RBX 132 
#define  VM_REG_GUEST_RCX 131 
#define  VM_REG_GUEST_RDI 130 
#define  VM_REG_GUEST_RDX 129 
#define  VM_REG_GUEST_RSI 128 

__attribute__((used)) static register_t *
swctx_regptr(struct svm_regctx *regctx, int reg)
{

	switch (reg) {
	case VM_REG_GUEST_RBX:
		return (&regctx->sctx_rbx);
	case VM_REG_GUEST_RCX:
		return (&regctx->sctx_rcx);
	case VM_REG_GUEST_RDX:
		return (&regctx->sctx_rdx);
	case VM_REG_GUEST_RDI:
		return (&regctx->sctx_rdi);
	case VM_REG_GUEST_RSI:
		return (&regctx->sctx_rsi);
	case VM_REG_GUEST_RBP:
		return (&regctx->sctx_rbp);
	case VM_REG_GUEST_R8:
		return (&regctx->sctx_r8);
	case VM_REG_GUEST_R9:
		return (&regctx->sctx_r9);
	case VM_REG_GUEST_R10:
		return (&regctx->sctx_r10);
	case VM_REG_GUEST_R11:
		return (&regctx->sctx_r11);
	case VM_REG_GUEST_R12:
		return (&regctx->sctx_r12);
	case VM_REG_GUEST_R13:
		return (&regctx->sctx_r13);
	case VM_REG_GUEST_R14:
		return (&regctx->sctx_r14);
	case VM_REG_GUEST_R15:
		return (&regctx->sctx_r15);
	case VM_REG_GUEST_DR0:
		return (&regctx->sctx_dr0);
	case VM_REG_GUEST_DR1:
		return (&regctx->sctx_dr1);
	case VM_REG_GUEST_DR2:
		return (&regctx->sctx_dr2);
	case VM_REG_GUEST_DR3:
		return (&regctx->sctx_dr3);
	default:
		return (NULL);
	}
}