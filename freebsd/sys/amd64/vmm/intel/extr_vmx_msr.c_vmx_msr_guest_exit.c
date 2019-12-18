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
struct vmx {int /*<<< orphan*/ ** guest_msrs; } ;

/* Variables and functions */
 size_t IDX_MSR_CSTAR ; 
 size_t IDX_MSR_KGSBASE ; 
 size_t IDX_MSR_LSTAR ; 
 size_t IDX_MSR_SF_MASK ; 
 size_t IDX_MSR_STAR ; 
 int /*<<< orphan*/  MSR_CSTAR ; 
 int /*<<< orphan*/  MSR_KGSBASE ; 
 int /*<<< orphan*/  MSR_LSTAR ; 
 int /*<<< orphan*/  MSR_SF_MASK ; 
 int /*<<< orphan*/  MSR_STAR ; 
 int /*<<< orphan*/ * host_msrs ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vmx_msr_guest_exit(struct vmx *vmx, int vcpuid)
{
	uint64_t *guest_msrs = vmx->guest_msrs[vcpuid];

	/* Save guest MSRs */
	guest_msrs[IDX_MSR_LSTAR] = rdmsr(MSR_LSTAR);
	guest_msrs[IDX_MSR_CSTAR] = rdmsr(MSR_CSTAR);
	guest_msrs[IDX_MSR_STAR] = rdmsr(MSR_STAR);
	guest_msrs[IDX_MSR_SF_MASK] = rdmsr(MSR_SF_MASK);
	guest_msrs[IDX_MSR_KGSBASE] = rdmsr(MSR_KGSBASE);

	/* Restore host MSRs */
	wrmsr(MSR_LSTAR, host_msrs[IDX_MSR_LSTAR]);
	wrmsr(MSR_CSTAR, host_msrs[IDX_MSR_CSTAR]);
	wrmsr(MSR_STAR, host_msrs[IDX_MSR_STAR]);
	wrmsr(MSR_SF_MASK, host_msrs[IDX_MSR_SF_MASK]);

	/* MSR_KGSBASE will be restored on the way back to userspace */
}