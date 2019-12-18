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
typedef  int uint64_t ;
struct xsave_limits {int xcr0_allowed; int /*<<< orphan*/  xsave_enabled; } ;
struct vmxctx {scalar_t__ guest_rcx; int guest_rdx; int guest_rax; } ;
struct vmx {int /*<<< orphan*/  vm; struct vmxctx* ctx; } ;
struct vm_exit {int dummy; } ;

/* Variables and functions */
 int CR4_XSAVE ; 
 int HANDLED ; 
 int /*<<< orphan*/  VMCS_GUEST_CR4 ; 
 int XFEATURE_AVX ; 
 int XFEATURE_AVX512 ; 
 int XFEATURE_ENABLED_AVX ; 
 int XFEATURE_ENABLED_BNDCSR ; 
 int XFEATURE_ENABLED_BNDREGS ; 
 int XFEATURE_ENABLED_X87 ; 
 int /*<<< orphan*/  load_xcr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_inject_gp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_inject_ud (int /*<<< orphan*/ ,int) ; 
 int vmcs_read (int /*<<< orphan*/ ) ; 
 struct xsave_limits* vmm_get_xsave_limits () ; 

__attribute__((used)) static int
vmx_emulate_xsetbv(struct vmx *vmx, int vcpu, struct vm_exit *vmexit)
{
	struct vmxctx *vmxctx;
	uint64_t xcrval;
	const struct xsave_limits *limits;

	vmxctx = &vmx->ctx[vcpu];
	limits = vmm_get_xsave_limits();

	/*
	 * Note that the processor raises a GP# fault on its own if
	 * xsetbv is executed for CPL != 0, so we do not have to
	 * emulate that fault here.
	 */

	/* Only xcr0 is supported. */
	if (vmxctx->guest_rcx != 0) {
		vm_inject_gp(vmx->vm, vcpu);
		return (HANDLED);
	}

	/* We only handle xcr0 if both the host and guest have XSAVE enabled. */
	if (!limits->xsave_enabled || !(vmcs_read(VMCS_GUEST_CR4) & CR4_XSAVE)) {
		vm_inject_ud(vmx->vm, vcpu);
		return (HANDLED);
	}

	xcrval = vmxctx->guest_rdx << 32 | (vmxctx->guest_rax & 0xffffffff);
	if ((xcrval & ~limits->xcr0_allowed) != 0) {
		vm_inject_gp(vmx->vm, vcpu);
		return (HANDLED);
	}

	if (!(xcrval & XFEATURE_ENABLED_X87)) {
		vm_inject_gp(vmx->vm, vcpu);
		return (HANDLED);
	}

	/* AVX (YMM_Hi128) requires SSE. */
	if (xcrval & XFEATURE_ENABLED_AVX &&
	    (xcrval & XFEATURE_AVX) != XFEATURE_AVX) {
		vm_inject_gp(vmx->vm, vcpu);
		return (HANDLED);
	}

	/*
	 * AVX512 requires base AVX (YMM_Hi128) as well as OpMask,
	 * ZMM_Hi256, and Hi16_ZMM.
	 */
	if (xcrval & XFEATURE_AVX512 &&
	    (xcrval & (XFEATURE_AVX512 | XFEATURE_AVX)) !=
	    (XFEATURE_AVX512 | XFEATURE_AVX)) {
		vm_inject_gp(vmx->vm, vcpu);
		return (HANDLED);
	}

	/*
	 * Intel MPX requires both bound register state flags to be
	 * set.
	 */
	if (((xcrval & XFEATURE_ENABLED_BNDREGS) != 0) !=
	    ((xcrval & XFEATURE_ENABLED_BNDCSR) != 0)) {
		vm_inject_gp(vmx->vm, vcpu);
		return (HANDLED);
	}

	/*
	 * This runs "inside" vmrun() with the guest's FPU state, so
	 * modifying xcr0 directly modifies the guest's xcr0, not the
	 * host's.
	 */
	load_xcr(0, xcrval);
	return (HANDLED);
}