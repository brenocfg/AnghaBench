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
 int /*<<< orphan*/  CPU_CLR (int,int /*<<< orphan*/ *) ; 
 scalar_t__ CPU_CMP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug (char*,int) ; 
 int /*<<< orphan*/  gdb_finish_suspend_vcpus () ; 
 int /*<<< orphan*/  gdb_lock ; 
 int /*<<< orphan*/  idle_vcpus ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stepping_vcpu ; 
 int /*<<< orphan*/  vcpus_suspended ; 
 int /*<<< orphan*/  vcpus_waiting ; 

__attribute__((used)) static void
_gdb_cpu_suspend(int vcpu, bool report_stop)
{

	debug("$vCPU %d suspending\n", vcpu);
	CPU_SET(vcpu, &vcpus_waiting);
	if (report_stop && CPU_CMP(&vcpus_waiting, &vcpus_suspended) == 0)
		gdb_finish_suspend_vcpus();
	while (CPU_ISSET(vcpu, &vcpus_suspended) && vcpu != stepping_vcpu)
		pthread_cond_wait(&idle_vcpus, &gdb_lock);
	CPU_CLR(vcpu, &vcpus_waiting);
	debug("$vCPU %d resuming\n", vcpu);
}