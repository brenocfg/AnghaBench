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
struct vmxctx {int host_tf; int /*<<< orphan*/  guest_dr6; int /*<<< orphan*/  guest_dr3; int /*<<< orphan*/  guest_dr2; int /*<<< orphan*/  guest_dr1; int /*<<< orphan*/  guest_dr0; int /*<<< orphan*/  host_dr6; int /*<<< orphan*/  host_dr3; int /*<<< orphan*/  host_dr2; int /*<<< orphan*/  host_dr1; int /*<<< orphan*/  host_dr0; int /*<<< orphan*/  host_debugctl; int /*<<< orphan*/  host_dr7; } ;
typedef  int register_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_DEBUGCTLMSR ; 
 int PSL_T ; 
 int /*<<< orphan*/  load_dr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_dr1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_dr2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_dr3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_dr6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_dr7 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdr0 () ; 
 int /*<<< orphan*/  rdr1 () ; 
 int /*<<< orphan*/  rdr2 () ; 
 int /*<<< orphan*/  rdr3 () ; 
 int /*<<< orphan*/  rdr6 () ; 
 int /*<<< orphan*/  rdr7 () ; 
 int read_rflags () ; 
 int /*<<< orphan*/  write_rflags (int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
vmx_dr_enter_guest(struct vmxctx *vmxctx)
{
	register_t rflags;

	/* Save host control debug registers. */
	vmxctx->host_dr7 = rdr7();
	vmxctx->host_debugctl = rdmsr(MSR_DEBUGCTLMSR);

	/*
	 * Disable debugging in DR7 and DEBUGCTL to avoid triggering
	 * exceptions in the host based on the guest DRx values.  The
	 * guest DR7 and DEBUGCTL are saved/restored in the VMCS.
	 */
	load_dr7(0);
	wrmsr(MSR_DEBUGCTLMSR, 0);

	/*
	 * Disable single stepping the kernel to avoid corrupting the
	 * guest DR6.  A debugger might still be able to corrupt the
	 * guest DR6 by setting a breakpoint after this point and then
	 * single stepping.
	 */
	rflags = read_rflags();
	vmxctx->host_tf = rflags & PSL_T;
	write_rflags(rflags & ~PSL_T);

	/* Save host debug registers. */
	vmxctx->host_dr0 = rdr0();
	vmxctx->host_dr1 = rdr1();
	vmxctx->host_dr2 = rdr2();
	vmxctx->host_dr3 = rdr3();
	vmxctx->host_dr6 = rdr6();

	/* Restore guest debug registers. */
	load_dr0(vmxctx->guest_dr0);
	load_dr1(vmxctx->guest_dr1);
	load_dr2(vmxctx->guest_dr2);
	load_dr3(vmxctx->guest_dr3);
	load_dr6(vmxctx->guest_dr6);
}