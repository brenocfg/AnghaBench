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
struct lockf_entry_list {int dummy; } ;
struct lockf_entry {int dummy; } ;
struct lockf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (struct lockf_entry_list*) ; 
 struct lockf_entry* LIST_FIRST (struct lockf_entry_list*) ; 
 int /*<<< orphan*/  LIST_INIT (struct lockf_entry_list*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct lockf_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lf_activate_lock (struct lockf*,struct lockf_entry*) ; 
 int /*<<< orphan*/  lf_free_lock (struct lockf_entry*) ; 
 int /*<<< orphan*/  lf_link ; 
 int /*<<< orphan*/  lf_owner_graph_lock ; 
 int /*<<< orphan*/  lf_remove_outgoing (struct lockf_entry*) ; 
 int /*<<< orphan*/  lf_update_dependancies (struct lockf*,struct lockf_entry*,int /*<<< orphan*/ ,struct lockf_entry_list*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lf_cancel_lock(struct lockf *state, struct lockf_entry *lock)
{
	struct lockf_entry_list granted;

	/*
	 * Note it is theoretically possible that cancelling this lock
	 * may allow some other pending lock to become
	 * active. Consider this case:
	 *
	 * Owner	Action		Result		Dependencies
	 * 
	 * A:		lock [0..0]	succeeds	
	 * B:		lock [2..2]	succeeds	
	 * C:		lock [1..2]	blocked		C->B
	 * D:		lock [0..1]	blocked		C->B,D->A,D->C
	 * A:		unlock [0..0]			C->B,D->C
	 * C:		cancel [1..2]	
	 */

	LIST_REMOVE(lock, lf_link);

	/*
	 * Removing out-going edges is simple.
	 */
	sx_xlock(&lf_owner_graph_lock);
	lf_remove_outgoing(lock);
	sx_xunlock(&lf_owner_graph_lock);

	/*
	 * Removing in-coming edges may allow some other lock to
	 * become active - we use lf_update_dependancies to figure
	 * this out.
	 */
	LIST_INIT(&granted);
	lf_update_dependancies(state, lock, TRUE, &granted);
	lf_free_lock(lock);

	/*
	 * Feed any newly active locks to lf_activate_lock.
	 */
	while (!LIST_EMPTY(&granted)) {
		lock = LIST_FIRST(&granted);
		LIST_REMOVE(lock, lf_link);
		lf_activate_lock(state, lock);
	}
}