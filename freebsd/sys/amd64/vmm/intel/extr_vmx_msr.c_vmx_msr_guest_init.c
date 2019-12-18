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
struct vmx {int** guest_msrs; } ;

/* Variables and functions */
 size_t IDX_MSR_PAT ; 
 int /*<<< orphan*/  MSR_CSTAR ; 
 int /*<<< orphan*/  MSR_KGSBASE ; 
 int /*<<< orphan*/  MSR_LSTAR ; 
 int /*<<< orphan*/  MSR_SF_MASK ; 
 int /*<<< orphan*/  MSR_STAR ; 
 int /*<<< orphan*/  PAT_UNCACHEABLE ; 
 int /*<<< orphan*/  PAT_UNCACHED ; 
 int PAT_VALUE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAT_WRITE_BACK ; 
 int /*<<< orphan*/  PAT_WRITE_THROUGH ; 
 int /*<<< orphan*/  guest_msr_rw (struct vmx*,int /*<<< orphan*/ ) ; 

void
vmx_msr_guest_init(struct vmx *vmx, int vcpuid)
{
	uint64_t *guest_msrs;

	guest_msrs = vmx->guest_msrs[vcpuid];

	/*
	 * The permissions bitmap is shared between all vcpus so initialize it
	 * once when initializing the vBSP.
	 */
	if (vcpuid == 0) {
		guest_msr_rw(vmx, MSR_LSTAR);
		guest_msr_rw(vmx, MSR_CSTAR);
		guest_msr_rw(vmx, MSR_STAR);
		guest_msr_rw(vmx, MSR_SF_MASK);
		guest_msr_rw(vmx, MSR_KGSBASE);
	}

	/*
	 * Initialize guest IA32_PAT MSR with default value after reset.
	 */
	guest_msrs[IDX_MSR_PAT] = PAT_VALUE(0, PAT_WRITE_BACK) |
	    PAT_VALUE(1, PAT_WRITE_THROUGH)	|
	    PAT_VALUE(2, PAT_UNCACHED)		|
	    PAT_VALUE(3, PAT_UNCACHEABLE)	|
	    PAT_VALUE(4, PAT_WRITE_BACK)	|
	    PAT_VALUE(5, PAT_WRITE_THROUGH)	|
	    PAT_VALUE(6, PAT_UNCACHED)		|
	    PAT_VALUE(7, PAT_UNCACHEABLE);

	return;
}