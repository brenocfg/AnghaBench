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
struct setlist {int dummy; } ;
struct cpuset {scalar_t__ cs_id; int /*<<< orphan*/  cs_ref; } ;

/* Variables and functions */
 scalar_t__ CPUSET_INVALID ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct setlist*,struct cpuset*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct cpuset*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuset_lock ; 
 int /*<<< orphan*/  cs_link ; 
 int /*<<< orphan*/  cs_siblings ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cpuset_rel_defer(struct setlist *head, struct cpuset *set)
{

	if (refcount_release(&set->cs_ref) == 0)
		return;
	mtx_lock_spin(&cpuset_lock);
	LIST_REMOVE(set, cs_siblings);
	if (set->cs_id != CPUSET_INVALID)
		LIST_REMOVE(set, cs_link);
	LIST_INSERT_HEAD(head, set, cs_link);
	mtx_unlock_spin(&cpuset_lock);
}