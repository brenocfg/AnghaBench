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
struct thread {int dummy; } ;
struct cpuset {int dummy; } ;
typedef  int /*<<< orphan*/  id_t ;
typedef  scalar_t__ cpuwhich_t ;
typedef  int /*<<< orphan*/  cpusetid_t ;

/* Variables and functions */
 scalar_t__ CPU_WHICH_PID ; 
 int EINVAL ; 
 int ESRCH ; 
 struct cpuset* cpuset_lookup (int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  cpuset_rel (struct cpuset*) ; 
 int cpuset_setproc (int /*<<< orphan*/ ,struct cpuset*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
kern_cpuset_setid(struct thread *td, cpuwhich_t which,
    id_t id, cpusetid_t setid)
{
	struct cpuset *set;
	int error;

	/*
	 * Presently we only support per-process sets.
	 */
	if (which != CPU_WHICH_PID)
		return (EINVAL);
	set = cpuset_lookup(setid, td);
	if (set == NULL)
		return (ESRCH);
	error = cpuset_setproc(id, set, NULL, NULL);
	cpuset_rel(set);
	return (error);
}