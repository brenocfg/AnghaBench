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
typedef  int u_int64_t ;

/* Variables and functions */
 int EFER_SCE ; 
 int /*<<< orphan*/  GCODE_SEL ; 
 scalar_t__ GSEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUCODE32_SEL ; 
 scalar_t__ IDTVEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_CSTAR ; 
 int /*<<< orphan*/  MSR_EFER ; 
 int /*<<< orphan*/  MSR_LSTAR ; 
 int /*<<< orphan*/  MSR_SF_MASK ; 
 int /*<<< orphan*/  MSR_STAR ; 
 int PSL_AC ; 
 int PSL_C ; 
 int PSL_D ; 
 int PSL_I ; 
 int PSL_NT ; 
 int PSL_T ; 
 int /*<<< orphan*/  SEL_KPL ; 
 int /*<<< orphan*/  SEL_UPL ; 
 int /*<<< orphan*/  fast_syscall ; 
 int /*<<< orphan*/  fast_syscall32 ; 
 int /*<<< orphan*/  fast_syscall_pti ; 
 scalar_t__ pti ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 

void
amd64_conf_fast_syscall(void)
{
	uint64_t msr;

	msr = rdmsr(MSR_EFER) | EFER_SCE;
	wrmsr(MSR_EFER, msr);
	wrmsr(MSR_LSTAR, pti ? (u_int64_t)IDTVEC(fast_syscall_pti) :
	    (u_int64_t)IDTVEC(fast_syscall));
	wrmsr(MSR_CSTAR, (u_int64_t)IDTVEC(fast_syscall32));
	msr = ((u_int64_t)GSEL(GCODE_SEL, SEL_KPL) << 32) |
	    ((u_int64_t)GSEL(GUCODE32_SEL, SEL_UPL) << 48);
	wrmsr(MSR_STAR, msr);
	wrmsr(MSR_SF_MASK, PSL_NT | PSL_T | PSL_I | PSL_C | PSL_D | PSL_AC);
}