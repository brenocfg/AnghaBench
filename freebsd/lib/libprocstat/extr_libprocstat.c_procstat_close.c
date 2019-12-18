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
struct procstat {scalar_t__ type; int /*<<< orphan*/  core; int /*<<< orphan*/  kd; } ;

/* Variables and functions */
 scalar_t__ PROCSTAT_CORE ; 
 scalar_t__ PROCSTAT_KVM ; 
 int /*<<< orphan*/  assert (struct procstat*) ; 
 int /*<<< orphan*/  free (struct procstat*) ; 
 int /*<<< orphan*/  kvm_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procstat_core_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procstat_freeargv (struct procstat*) ; 
 int /*<<< orphan*/  procstat_freeenvv (struct procstat*) ; 

void
procstat_close(struct procstat *procstat)
{

	assert(procstat);
	if (procstat->type == PROCSTAT_KVM)
		kvm_close(procstat->kd);
	else if (procstat->type == PROCSTAT_CORE)
		procstat_core_close(procstat->core);
	procstat_freeargv(procstat);
	procstat_freeenvv(procstat);
	free(procstat);
}