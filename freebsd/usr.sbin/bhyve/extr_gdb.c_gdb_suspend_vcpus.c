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
 scalar_t__ CPU_CMP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  gdb_finish_suspend_vcpus () ; 
 int /*<<< orphan*/  gdb_lock ; 
 int /*<<< orphan*/  pthread_mutex_isowned_np (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcpus_active ; 
 int /*<<< orphan*/  vcpus_suspended ; 
 int /*<<< orphan*/  vcpus_waiting ; 
 int /*<<< orphan*/  vm_suspend_cpu (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
gdb_suspend_vcpus(void)
{

	assert(pthread_mutex_isowned_np(&gdb_lock));
	debug("suspending all CPUs\n");
	vcpus_suspended = vcpus_active;
	vm_suspend_cpu(ctx, -1);
	if (CPU_CMP(&vcpus_waiting, &vcpus_suspended) == 0)
		gdb_finish_suspend_vcpus();
}