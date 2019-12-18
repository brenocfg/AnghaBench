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
struct vmxctx {int host_tf; int /*<<< orphan*/  host_dr7; int /*<<< orphan*/  host_debugctl; int /*<<< orphan*/  host_dr6; int /*<<< orphan*/  host_dr3; int /*<<< orphan*/  host_dr2; int /*<<< orphan*/  host_dr1; int /*<<< orphan*/  host_dr0; int /*<<< orphan*/  guest_dr6; int /*<<< orphan*/  guest_dr3; int /*<<< orphan*/  guest_dr2; int /*<<< orphan*/  guest_dr1; int /*<<< orphan*/  guest_dr0; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_DEBUGCTLMSR ; 
 int /*<<< orphan*/  load_dr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_dr1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_dr2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_dr3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_dr6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_dr7 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdr0 () ; 
 int /*<<< orphan*/  rdr1 () ; 
 int /*<<< orphan*/  rdr2 () ; 
 int /*<<< orphan*/  rdr3 () ; 
 int /*<<< orphan*/  rdr6 () ; 
 int read_rflags () ; 
 int /*<<< orphan*/  write_rflags (int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
vmx_dr_leave_guest(struct vmxctx *vmxctx)
{

	/* Save guest debug registers. */
	vmxctx->guest_dr0 = rdr0();
	vmxctx->guest_dr1 = rdr1();
	vmxctx->guest_dr2 = rdr2();
	vmxctx->guest_dr3 = rdr3();
	vmxctx->guest_dr6 = rdr6();

	/*
	 * Restore host debug registers.  Restore DR7, DEBUGCTL, and
	 * PSL_T last.
	 */
	load_dr0(vmxctx->host_dr0);
	load_dr1(vmxctx->host_dr1);
	load_dr2(vmxctx->host_dr2);
	load_dr3(vmxctx->host_dr3);
	load_dr6(vmxctx->host_dr6);
	wrmsr(MSR_DEBUGCTLMSR, vmxctx->host_debugctl);
	load_dr7(vmxctx->host_dr7);
	write_rflags(read_rflags() | vmxctx->host_tf);
}