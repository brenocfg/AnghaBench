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
struct cpuset {scalar_t__ cs_id; struct cpuset* cs_parent; int /*<<< orphan*/  cs_ref; } ;
typedef  scalar_t__ cpusetid_t ;

/* Variables and functions */
 scalar_t__ CPUSET_INVALID ; 
 int /*<<< orphan*/  LIST_REMOVE (struct cpuset*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuset_lock ; 
 int /*<<< orphan*/  cpuset_unr ; 
 int /*<<< orphan*/  cpuset_zone ; 
 int /*<<< orphan*/  cs_link ; 
 int /*<<< orphan*/  cs_siblings ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct cpuset*) ; 

void
cpuset_rel(struct cpuset *set)
{
	cpusetid_t id;

	if (refcount_release(&set->cs_ref) == 0)
		return;
	mtx_lock_spin(&cpuset_lock);
	LIST_REMOVE(set, cs_siblings);
	id = set->cs_id;
	if (id != CPUSET_INVALID)
		LIST_REMOVE(set, cs_link);
	mtx_unlock_spin(&cpuset_lock);
	cpuset_rel(set->cs_parent);
	uma_zfree(cpuset_zone, set);
	if (id != CPUSET_INVALID)
		free_unr(cpuset_unr, id);
}