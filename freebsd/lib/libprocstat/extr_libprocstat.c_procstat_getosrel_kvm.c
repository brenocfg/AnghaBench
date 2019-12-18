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
struct proc {int p_osrel; } ;
struct kinfo_proc {int /*<<< orphan*/  ki_pid; scalar_t__ ki_paddr; } ;
typedef  int /*<<< orphan*/  proc ;
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_read_all (int /*<<< orphan*/ *,unsigned long,struct proc*,int) ; 
 int /*<<< orphan*/  warnx (char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
procstat_getosrel_kvm(kvm_t *kd, struct kinfo_proc *kp, int *osrelp)
{
	struct proc proc;

	assert(kd != NULL);
	assert(kp != NULL);
	if (!kvm_read_all(kd, (unsigned long)kp->ki_paddr, &proc,
	    sizeof(proc))) {
		warnx("can't read proc struct at %p for pid %d",
		    kp->ki_paddr, kp->ki_pid);
		return (-1);
	}
	*osrelp = proc.p_osrel;
	return (0);
}