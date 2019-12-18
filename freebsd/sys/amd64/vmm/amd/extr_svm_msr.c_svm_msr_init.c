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

/* Variables and functions */
 size_t IDX_MSR_CSTAR ; 
 size_t IDX_MSR_LSTAR ; 
 size_t IDX_MSR_SF_MASK ; 
 size_t IDX_MSR_STAR ; 
 int /*<<< orphan*/  MSR_CSTAR ; 
 int /*<<< orphan*/  MSR_LSTAR ; 
 int /*<<< orphan*/  MSR_SF_MASK ; 
 int /*<<< orphan*/  MSR_STAR ; 
 int /*<<< orphan*/ * host_msrs ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ) ; 

void
svm_msr_init(void)
{
	/* 
	 * It is safe to cache the values of the following MSRs because they
	 * don't change based on curcpu, curproc or curthread.
	 */
	host_msrs[IDX_MSR_LSTAR] = rdmsr(MSR_LSTAR);
	host_msrs[IDX_MSR_CSTAR] = rdmsr(MSR_CSTAR);
	host_msrs[IDX_MSR_STAR] = rdmsr(MSR_STAR);
	host_msrs[IDX_MSR_SF_MASK] = rdmsr(MSR_SF_MASK);
}