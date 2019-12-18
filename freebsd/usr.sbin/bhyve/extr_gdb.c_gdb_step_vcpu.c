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
 int /*<<< orphan*/  VM_CAP_MTRAP_EXIT ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  debug (char*,int) ; 
 int /*<<< orphan*/  idle_vcpus ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int stepping_vcpu ; 
 int vm_get_capability (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vm_resume_cpu (int /*<<< orphan*/ ,int) ; 
 int vm_set_capability (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
gdb_step_vcpu(int vcpu)
{
	int error, val;

	debug("$vCPU %d step\n", vcpu);
	error = vm_get_capability(ctx, vcpu, VM_CAP_MTRAP_EXIT, &val);
	if (error < 0)
		return (false);
	error = vm_set_capability(ctx, vcpu, VM_CAP_MTRAP_EXIT, 1);
	vm_resume_cpu(ctx, vcpu);
	stepping_vcpu = vcpu;
	pthread_cond_broadcast(&idle_vcpus);
	return (true);
}