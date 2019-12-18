#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ref_iterator {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  oid; int /*<<< orphan*/  refname; } ;
struct files_ref_iterator {int flags; TYPE_2__* iter0; TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  oid; int /*<<< orphan*/  refname; } ;

/* Variables and functions */
 int DO_FOR_EACH_INCLUDE_BROKEN ; 
 int DO_FOR_EACH_PER_WORKTREE_ONLY ; 
 scalar_t__ ITER_DONE ; 
 int ITER_ERROR ; 
 int ITER_OK ; 
 scalar_t__ REF_TYPE_PER_WORKTREE ; 
 scalar_t__ ref_iterator_abort (struct ref_iterator*) ; 
 int ref_iterator_advance (TYPE_2__*) ; 
 int /*<<< orphan*/  ref_resolves_to_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ref_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int files_ref_iterator_advance(struct ref_iterator *ref_iterator)
{
	struct files_ref_iterator *iter =
		(struct files_ref_iterator *)ref_iterator;
	int ok;

	while ((ok = ref_iterator_advance(iter->iter0)) == ITER_OK) {
		if (iter->flags & DO_FOR_EACH_PER_WORKTREE_ONLY &&
		    ref_type(iter->iter0->refname) != REF_TYPE_PER_WORKTREE)
			continue;

		if (!(iter->flags & DO_FOR_EACH_INCLUDE_BROKEN) &&
		    !ref_resolves_to_object(iter->iter0->refname,
					    iter->iter0->oid,
					    iter->iter0->flags))
			continue;

		iter->base.refname = iter->iter0->refname;
		iter->base.oid = iter->iter0->oid;
		iter->base.flags = iter->iter0->flags;
		return ITER_OK;
	}

	iter->iter0 = NULL;
	if (ref_iterator_abort(ref_iterator) != ITER_DONE)
		ok = ITER_ERROR;

	return ok;
}