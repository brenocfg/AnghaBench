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
 int /*<<< orphan*/  CPU_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _gdb_cpu_suspend (int,int) ; 
 int /*<<< orphan*/  debug (char*,int) ; 
 int /*<<< orphan*/  gdb_lock ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcpus_active ; 
 int /*<<< orphan*/  vcpus_suspended ; 

void
gdb_cpu_add(int vcpu)
{

	debug("$vCPU %d starting\n", vcpu);
	pthread_mutex_lock(&gdb_lock);
	CPU_SET(vcpu, &vcpus_active);

	/*
	 * If a vcpu is added while vcpus are stopped, suspend the new
	 * vcpu so that it will pop back out with a debug exit before
	 * executing the first instruction.
	 */
	if (!CPU_EMPTY(&vcpus_suspended)) {
		CPU_SET(vcpu, &vcpus_suspended);
		_gdb_cpu_suspend(vcpu, false);
	}
	pthread_mutex_unlock(&gdb_lock);
}