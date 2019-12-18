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
struct lockf_entry {scalar_t__ lf_type; int /*<<< orphan*/  lf_end; int /*<<< orphan*/  lf_start; } ;
struct lockf {struct lockf_entry_list ls_active; } ;

/* Variables and functions */
 scalar_t__ F_UNLCK ; 
 int /*<<< orphan*/  LIST_EMPTY (struct lockf_entry_list*) ; 
 struct lockf_entry* LIST_FIRST (struct lockf_entry_list*) ; 
 int /*<<< orphan*/  LIST_INIT (struct lockf_entry_list*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct lockf_entry_list*,struct lockf_entry*,int /*<<< orphan*/ ) ; 
 struct lockf_entry* LIST_NEXT (struct lockf_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct lockf_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SELF ; 
 int /*<<< orphan*/  TRUE ; 
 int lf_findoverlap (struct lockf_entry**,struct lockf_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lf_free_lock (struct lockf_entry*) ; 
 int /*<<< orphan*/  lf_insert_lock (struct lockf*,struct lockf_entry*) ; 
 int /*<<< orphan*/  lf_link ; 
 int /*<<< orphan*/  lf_print (char*,struct lockf_entry*) ; 
 int /*<<< orphan*/  lf_printlist (char*,struct lockf_entry*) ; 
 int /*<<< orphan*/  lf_set_end (struct lockf*,struct lockf_entry*,int /*<<< orphan*/ ,struct lockf_entry_list*) ; 
 int /*<<< orphan*/  lf_set_start (struct lockf*,struct lockf_entry*,int /*<<< orphan*/ ,struct lockf_entry_list*) ; 
 int /*<<< orphan*/  lf_split (struct lockf*,struct lockf_entry*,struct lockf_entry*,struct lockf_entry_list*) ; 
 int /*<<< orphan*/  lf_update_dependancies (struct lockf*,struct lockf_entry*,int /*<<< orphan*/ ,struct lockf_entry_list*) ; 
 int lockf_debug ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
lf_activate_lock(struct lockf *state, struct lockf_entry *lock)
{
	struct lockf_entry *overlap, *lf;
	struct lockf_entry_list granted;
	int ovcase;

	LIST_INIT(&granted);
	LIST_INSERT_HEAD(&granted, lock, lf_link);

	while (!LIST_EMPTY(&granted)) {
		lock = LIST_FIRST(&granted);
		LIST_REMOVE(lock, lf_link);

		/*
		 * Skip over locks owned by other processes.  Handle
		 * any locks that overlap and are owned by ourselves.
		 */
		overlap = LIST_FIRST(&state->ls_active);
		for (;;) {
			ovcase = lf_findoverlap(&overlap, lock, SELF);

#ifdef LOCKF_DEBUG
			if (ovcase && (lockf_debug & 2)) {
				printf("lf_setlock: overlap %d", ovcase);
				lf_print("", overlap);
			}
#endif
			/*
			 * Six cases:
			 *	0) no overlap
			 *	1) overlap == lock
			 *	2) overlap contains lock
			 *	3) lock contains overlap
			 *	4) overlap starts before lock
			 *	5) overlap ends after lock
			 */
			switch (ovcase) {
			case 0: /* no overlap */
				break;

			case 1: /* overlap == lock */
				/*
				 * We have already setup the
				 * dependants for the new lock, taking
				 * into account a possible downgrade
				 * or unlock. Remove the old lock.
				 */
				LIST_REMOVE(overlap, lf_link);
				lf_update_dependancies(state, overlap, TRUE,
					&granted);
				lf_free_lock(overlap);
				break;

			case 2: /* overlap contains lock */
				/*
				 * Just split the existing lock.
				 */
				lf_split(state, overlap, lock, &granted);
				break;

			case 3: /* lock contains overlap */
				/*
				 * Delete the overlap and advance to
				 * the next entry in the list.
				 */
				lf = LIST_NEXT(overlap, lf_link);
				LIST_REMOVE(overlap, lf_link);
				lf_update_dependancies(state, overlap, TRUE,
					&granted);
				lf_free_lock(overlap);
				overlap = lf;
				continue;

			case 4: /* overlap starts before lock */
				/*
				 * Just update the overlap end and
				 * move on.
				 */
				lf_set_end(state, overlap, lock->lf_start - 1,
				    &granted);
				overlap = LIST_NEXT(overlap, lf_link);
				continue;

			case 5: /* overlap ends after lock */
				/*
				 * Change the start of overlap and
				 * re-insert.
				 */
				lf_set_start(state, overlap, lock->lf_end + 1,
				    &granted);
				break;
			}
			break;
		}
#ifdef LOCKF_DEBUG
		if (lockf_debug & 1) {
			if (lock->lf_type != F_UNLCK)
				lf_print("lf_activate_lock: activated", lock);
			else
				lf_print("lf_activate_lock: unlocked", lock);
			lf_printlist("lf_activate_lock", lock);
		}
#endif /* LOCKF_DEBUG */
		if (lock->lf_type != F_UNLCK)
			lf_insert_lock(state, lock);
	}
}