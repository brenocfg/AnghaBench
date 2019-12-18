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
struct lockf_entry {scalar_t__ lf_start; } ;
struct lockf {int dummy; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct lockf_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lf_insert_lock (struct lockf*,struct lockf_entry*) ; 
 int /*<<< orphan*/  lf_link ; 
 int /*<<< orphan*/  lf_update_dependancies (struct lockf*,struct lockf_entry*,int /*<<< orphan*/ ,struct lockf_entry_list*) ; 

__attribute__((used)) static void
lf_set_start(struct lockf *state, struct lockf_entry *lock, off_t new_start,
	struct lockf_entry_list *granted)
{

	KASSERT(new_start >= lock->lf_start, ("can't increase lock"));
	lock->lf_start = new_start;
	LIST_REMOVE(lock, lf_link);
	lf_insert_lock(state, lock);
	lf_update_dependancies(state, lock, FALSE, granted);
}