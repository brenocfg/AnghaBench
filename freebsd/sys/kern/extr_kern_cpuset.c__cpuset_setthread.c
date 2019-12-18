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
struct thread {int /*<<< orphan*/  td_cpuset; } ;
struct setlist {int dummy; } ;
struct proc {int dummy; } ;
struct domainset {int dummy; } ;
struct domainlist {int dummy; } ;
struct cpuset {int dummy; } ;
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_WHICH_TID ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  cpuset_freelist_free (struct setlist*) ; 
 int /*<<< orphan*/  cpuset_freelist_init (struct setlist*,int) ; 
 int /*<<< orphan*/  cpuset_rel (struct cpuset*) ; 
 int cpuset_shadow (int /*<<< orphan*/ ,struct cpuset**,int /*<<< orphan*/ *,struct domainset*,struct setlist*,struct domainlist*) ; 
 struct cpuset* cpuset_update_thread (struct thread*,struct cpuset*) ; 
 int cpuset_which (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proc**,struct thread**,struct cpuset**) ; 
 int /*<<< orphan*/  domainset_freelist_free (struct domainlist*) ; 
 int /*<<< orphan*/  domainset_freelist_init (struct domainlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

__attribute__((used)) static int
_cpuset_setthread(lwpid_t id, cpuset_t *mask, struct domainset *domain)
{
	struct setlist cpusets;
	struct domainlist domainlist;
	struct cpuset *nset;
	struct cpuset *set;
	struct thread *td;
	struct proc *p;
	int error;

	cpuset_freelist_init(&cpusets, 1);
	domainset_freelist_init(&domainlist, domain != NULL);
	error = cpuset_which(CPU_WHICH_TID, id, &p, &td, &set);
	if (error)
		goto out;
	set = NULL;
	thread_lock(td);
	error = cpuset_shadow(td->td_cpuset, &nset, mask, domain,
	    &cpusets, &domainlist);
	if (error == 0)
		set = cpuset_update_thread(td, nset);
	thread_unlock(td);
	PROC_UNLOCK(p);
	if (set)
		cpuset_rel(set);
out:
	cpuset_freelist_free(&cpusets);
	domainset_freelist_free(&domainlist);
	return (error);
}