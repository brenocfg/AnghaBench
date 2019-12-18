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
 int /*<<< orphan*/  curpcb ; 
 int /*<<< orphan*/  update_pcb_bases (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vmx_msr_guest_enter(struct vmx *vmx, int vcpuid)
{
	uint64_t *guest_msrs = vmx->guest_msrs[vcpuid];

	/* Save host MSRs (in particular, KGSBASE) and restore guest MSRs */
	update_pcb_bases(curpcb);
	wrmsr(MSR_LSTAR, guest_msrs[IDX_MSR_LSTAR]);
	wrmsr(MSR_CSTAR, guest_msrs[IDX_MSR_CSTAR]);
	wrmsr(MSR_STAR, guest_msrs[IDX_MSR_STAR]);
	wrmsr(MSR_SF_MASK, guest_msrs[IDX_MSR_SF_MASK]);
	wrmsr(MSR_KGSBASE, guest_msrs[IDX_MSR_KGSBASE]);
}