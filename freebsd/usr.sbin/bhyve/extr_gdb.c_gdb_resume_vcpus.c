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
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  gdb_lock ; 
 int /*<<< orphan*/  idle_vcpus ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_isowned_np (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcpus_suspended ; 
 int /*<<< orphan*/  vm_resume_cpu (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
gdb_resume_vcpus(void)
{

	assert(pthread_mutex_isowned_np(&gdb_lock));
	vm_resume_cpu(ctx, -1);
	debug("resuming all CPUs\n");
	CPU_ZERO(&vcpus_suspended);
	pthread_cond_broadcast(&idle_vcpus);
}