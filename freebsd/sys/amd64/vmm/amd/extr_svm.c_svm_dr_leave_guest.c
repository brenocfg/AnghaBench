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
struct svm_regctx {int /*<<< orphan*/  host_dr7; int /*<<< orphan*/  host_debugctl; int /*<<< orphan*/  host_dr6; int /*<<< orphan*/  host_dr3; int /*<<< orphan*/  host_dr2; int /*<<< orphan*/  host_dr1; int /*<<< orphan*/  host_dr0; int /*<<< orphan*/  sctx_dr3; int /*<<< orphan*/  sctx_dr2; int /*<<< orphan*/  sctx_dr1; int /*<<< orphan*/  sctx_dr0; } ;

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
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
svm_dr_leave_guest(struct svm_regctx *gctx)
{

	/* Save guest debug registers. */
	gctx->sctx_dr0 = rdr0();
	gctx->sctx_dr1 = rdr1();
	gctx->sctx_dr2 = rdr2();
	gctx->sctx_dr3 = rdr3();

	/*
	 * Restore host debug registers.  Restore DR7 and DEBUGCTL
	 * last.
	 */
	load_dr0(gctx->host_dr0);
	load_dr1(gctx->host_dr1);
	load_dr2(gctx->host_dr2);
	load_dr3(gctx->host_dr3);
	load_dr6(gctx->host_dr6);
	wrmsr(MSR_DEBUGCTLMSR, gctx->host_debugctl);
	load_dr7(gctx->host_dr7);
}