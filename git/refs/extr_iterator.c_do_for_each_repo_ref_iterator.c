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
struct repository {int dummy; } ;
struct ref_iterator {int /*<<< orphan*/  flags; int /*<<< orphan*/  oid; int /*<<< orphan*/  refname; } ;
typedef  int (* each_repo_ref_fn ) (struct repository*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;

/* Variables and functions */
 int ITER_ERROR ; 
 int ITER_OK ; 
 struct ref_iterator* current_ref_iter ; 
 int /*<<< orphan*/  ref_iterator_abort (struct ref_iterator*) ; 
 int ref_iterator_advance (struct ref_iterator*) ; 

int do_for_each_repo_ref_iterator(struct repository *r, struct ref_iterator *iter,
				  each_repo_ref_fn fn, void *cb_data)
{
	int retval = 0, ok;
	struct ref_iterator *old_ref_iter = current_ref_iter;

	current_ref_iter = iter;
	while ((ok = ref_iterator_advance(iter)) == ITER_OK) {
		retval = fn(r, iter->refname, iter->oid, iter->flags, cb_data);
		if (retval) {
			/*
			 * If ref_iterator_abort() returns ITER_ERROR,
			 * we ignore that error in deference to the
			 * callback function's return value.
			 */
			ref_iterator_abort(iter);
			goto out;
		}
	}

out:
	current_ref_iter = old_ref_iter;
	if (ok == ITER_ERROR)
		return -1;
	return retval;
}