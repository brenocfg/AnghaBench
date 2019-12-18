#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct vmctx {int dummy; } ;
struct TYPE_5__ {int mt_vcpu; int /*<<< orphan*/  mt_thr; struct vmctx* mt_ctx; } ;
struct TYPE_4__ {scalar_t__ inst_length; int /*<<< orphan*/  rip; } ;

/* Variables and functions */
 int BSP ; 
 int /*<<< orphan*/  CPU_SET_ATOMIC (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cpumask ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fbsdrun_start_thread ; 
 TYPE_2__* mt_vmm_info ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int vm_activate_cpu (struct vmctx*,int) ; 
 TYPE_1__* vmexit ; 

void
fbsdrun_addcpu(struct vmctx *ctx, int fromcpu, int newcpu, uint64_t rip)
{
	int error;

	assert(fromcpu == BSP);

	/*
	 * The 'newcpu' must be activated in the context of 'fromcpu'. If
	 * vm_activate_cpu() is delayed until newcpu's pthread starts running
	 * then vmm.ko is out-of-sync with bhyve and this can create a race
	 * with vm_suspend().
	 */
	error = vm_activate_cpu(ctx, newcpu);
	if (error != 0)
		err(EX_OSERR, "could not activate CPU %d", newcpu);

	CPU_SET_ATOMIC(newcpu, &cpumask);

	/*
	 * Set up the vmexit struct to allow execution to start
	 * at the given RIP
	 */
	vmexit[newcpu].rip = rip;
	vmexit[newcpu].inst_length = 0;

	mt_vmm_info[newcpu].mt_ctx = ctx;
	mt_vmm_info[newcpu].mt_vcpu = newcpu;

	error = pthread_create(&mt_vmm_info[newcpu].mt_thr, NULL,
	    fbsdrun_start_thread, &mt_vmm_info[newcpu]);
	assert(error == 0);
}