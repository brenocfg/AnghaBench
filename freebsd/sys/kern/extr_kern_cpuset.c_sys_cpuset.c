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
struct cpuset_args {int /*<<< orphan*/  setid; } ;
struct cpuset {int /*<<< orphan*/  cs_id; int /*<<< orphan*/  cs_mask; } ;

/* Variables and functions */
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int cpuset_create (struct cpuset**,struct cpuset*,int /*<<< orphan*/ *) ; 
 struct cpuset* cpuset_refroot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuset_rel (struct cpuset*) ; 
 int cpuset_setproc (int,struct cpuset*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

int
sys_cpuset(struct thread *td, struct cpuset_args *uap)
{
	struct cpuset *root;
	struct cpuset *set;
	int error;

	thread_lock(td);
	root = cpuset_refroot(td->td_cpuset);
	thread_unlock(td);
	error = cpuset_create(&set, root, &root->cs_mask);
	cpuset_rel(root);
	if (error)
		return (error);
	error = copyout(&set->cs_id, uap->setid, sizeof(set->cs_id));
	if (error == 0)
		error = cpuset_setproc(-1, set, NULL, NULL);
	cpuset_rel(set);
	return (error);
}