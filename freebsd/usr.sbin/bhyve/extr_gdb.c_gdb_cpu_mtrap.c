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
 int /*<<< orphan*/  _gdb_cpu_suspend (int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  debug (char*,int) ; 
 int /*<<< orphan*/  gdb_lock ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int stepping_vcpu ; 
 int stopped_vcpu ; 
 int /*<<< orphan*/  vm_set_capability (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_suspend_cpu (int /*<<< orphan*/ ,int) ; 

void
gdb_cpu_mtrap(int vcpu)
{

	debug("$vCPU %d MTRAP\n", vcpu);
	pthread_mutex_lock(&gdb_lock);
	if (vcpu == stepping_vcpu) {
		stepping_vcpu = -1;
		vm_set_capability(ctx, vcpu, VM_CAP_MTRAP_EXIT, 0);
		vm_suspend_cpu(ctx, vcpu);
		assert(stopped_vcpu == -1);
		stopped_vcpu = vcpu;
		_gdb_cpu_suspend(vcpu, true);
	}
	pthread_mutex_unlock(&gdb_lock);
}