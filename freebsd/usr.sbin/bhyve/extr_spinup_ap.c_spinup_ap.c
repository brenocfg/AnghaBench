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
struct vmctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_CAP_UNRESTRICTED_GUEST ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fbsdrun_addcpu (struct vmctx*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fbsdrun_set_capabilities (struct vmctx*,int) ; 
 int guest_ncpus ; 
 int /*<<< orphan*/  spinup_ap_realmode (struct vmctx*,int,int /*<<< orphan*/ *) ; 
 int vcpu_reset (struct vmctx*,int) ; 
 int vm_set_capability (struct vmctx*,int,int /*<<< orphan*/ ,int) ; 

int
spinup_ap(struct vmctx *ctx, int vcpu, int newcpu, uint64_t rip)
{
	int error;

	assert(newcpu != 0);
	assert(newcpu < guest_ncpus);

	error = vcpu_reset(ctx, newcpu);
	assert(error == 0);

	fbsdrun_set_capabilities(ctx, newcpu);

	/*
	 * Enable the 'unrestricted guest' mode for 'newcpu'.
	 *
	 * Set up the processor state in power-on 16-bit mode, with the CS:IP
	 * init'd to the specified low-mem 4K page.
	 */
	error = vm_set_capability(ctx, newcpu, VM_CAP_UNRESTRICTED_GUEST, 1);
	assert(error == 0);

	spinup_ap_realmode(ctx, newcpu, &rip);

	fbsdrun_addcpu(ctx, vcpu, newcpu, rip);

	return (newcpu);
}