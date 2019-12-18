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
struct vmxctx {int /*<<< orphan*/  guest_r15; int /*<<< orphan*/  guest_r14; int /*<<< orphan*/  guest_r13; int /*<<< orphan*/  guest_r12; int /*<<< orphan*/  guest_r11; int /*<<< orphan*/  guest_r10; int /*<<< orphan*/  guest_r9; int /*<<< orphan*/  guest_r8; int /*<<< orphan*/  guest_rdi; int /*<<< orphan*/  guest_rsi; int /*<<< orphan*/  guest_rbp; int /*<<< orphan*/  guest_rbx; int /*<<< orphan*/  guest_rdx; int /*<<< orphan*/  guest_rcx; int /*<<< orphan*/  guest_rax; } ;
struct vmx {struct vmxctx* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCS_GUEST_RSP ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  vmcs_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
vmx_get_guest_reg(struct vmx *vmx, int vcpu, int ident)
{
	const struct vmxctx *vmxctx;

	vmxctx = &vmx->ctx[vcpu];

	switch (ident) {
	case 0:
		return (vmxctx->guest_rax);
	case 1:
		return (vmxctx->guest_rcx);
	case 2:
		return (vmxctx->guest_rdx);
	case 3:
		return (vmxctx->guest_rbx);
	case 4:
		return (vmcs_read(VMCS_GUEST_RSP));
	case 5:
		return (vmxctx->guest_rbp);
	case 6:
		return (vmxctx->guest_rsi);
	case 7:
		return (vmxctx->guest_rdi);
	case 8:
		return (vmxctx->guest_r8);
	case 9:
		return (vmxctx->guest_r9);
	case 10:
		return (vmxctx->guest_r10);
	case 11:
		return (vmxctx->guest_r11);
	case 12:
		return (vmxctx->guest_r12);
	case 13:
		return (vmxctx->guest_r13);
	case 14:
		return (vmxctx->guest_r14);
	case 15:
		return (vmxctx->guest_r15);
	default:
		panic("invalid vmx register %d", ident);
	}
}