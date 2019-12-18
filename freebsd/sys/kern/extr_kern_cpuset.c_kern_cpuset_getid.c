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
typedef  int /*<<< orphan*/  tmpid ;
struct thread {int /*<<< orphan*/  td_cpuset; } ;
struct proc {int dummy; } ;
struct cpuset {int /*<<< orphan*/  cs_id; } ;
typedef  int /*<<< orphan*/  id_t ;
typedef  int cpuwhich_t ;
typedef  int /*<<< orphan*/  cpusetid_t ;
typedef  int cpulevel_t ;

/* Variables and functions */
#define  CPU_LEVEL_CPUSET 136 
#define  CPU_LEVEL_ROOT 135 
#define  CPU_LEVEL_WHICH 134 
#define  CPU_WHICH_CPUSET 133 
#define  CPU_WHICH_DOMAIN 132 
#define  CPU_WHICH_IRQ 131 
#define  CPU_WHICH_JAIL 130 
#define  CPU_WHICH_PID 129 
#define  CPU_WHICH_TID 128 
 int EINVAL ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct cpuset* cpuset_refbase (int /*<<< orphan*/ ) ; 
 struct cpuset* cpuset_refroot (struct cpuset*) ; 
 int /*<<< orphan*/  cpuset_rel (struct cpuset*) ; 
 int cpuset_which (int,int /*<<< orphan*/ ,struct proc**,struct thread**,struct cpuset**) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

int
kern_cpuset_getid(struct thread *td, cpulevel_t level, cpuwhich_t which,
    id_t id, cpusetid_t *setid)
{
	struct cpuset *nset;
	struct cpuset *set;
	struct thread *ttd;
	struct proc *p;
	cpusetid_t tmpid;
	int error;

	if (level == CPU_LEVEL_WHICH && which != CPU_WHICH_CPUSET)
		return (EINVAL);
	error = cpuset_which(which, id, &p, &ttd, &set);
	if (error)
		return (error);
	switch (which) {
	case CPU_WHICH_TID:
	case CPU_WHICH_PID:
		thread_lock(ttd);
		set = cpuset_refbase(ttd->td_cpuset);
		thread_unlock(ttd);
		PROC_UNLOCK(p);
		break;
	case CPU_WHICH_CPUSET:
	case CPU_WHICH_JAIL:
		break;
	case CPU_WHICH_IRQ:
	case CPU_WHICH_DOMAIN:
		return (EINVAL);
	}
	switch (level) {
	case CPU_LEVEL_ROOT:
		nset = cpuset_refroot(set);
		cpuset_rel(set);
		set = nset;
		break;
	case CPU_LEVEL_CPUSET:
		break;
	case CPU_LEVEL_WHICH:
		break;
	}
	tmpid = set->cs_id;
	cpuset_rel(set);
	if (error == 0)
		error = copyout(&tmpid, setid, sizeof(tmpid));

	return (error);
}