#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_pool ;
struct TYPE_8__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  size; int /*<<< orphan*/  mode; int /*<<< orphan*/  id; } ;
struct TYPE_9__ {scalar_t__ status; int nfiles; TYPE_1__ old_file; } ;
typedef  TYPE_2__ git_diff_delta ;

/* Variables and functions */
 scalar_t__ GIT_DELTA_ADDED ; 
 scalar_t__ GIT_DELTA_CONFLICTED ; 
 scalar_t__ GIT_DELTA_DELETED ; 
 scalar_t__ GIT_DELTA_UNMODIFIED ; 
 scalar_t__ GIT_DELTA_UNREADABLE ; 
 scalar_t__ GIT_DELTA_UNTRACKED ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* git_diff__delta_dup (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

git_diff_delta *git_diff__merge_like_cgit(
	const git_diff_delta *a,
	const git_diff_delta *b,
	git_pool *pool)
{
	git_diff_delta *dup;

	/* Emulate C git for merging two diffs (a la 'git diff <sha>').
	 *
	 * When C git does a diff between the work dir and a tree, it actually
	 * diffs with the index but uses the workdir contents.  This emulates
	 * those choices so we can emulate the type of diff.
	 *
	 * We have three file descriptions here, let's call them:
	 *  f1 = a->old_file
	 *  f2 = a->new_file AND b->old_file
	 *  f3 = b->new_file
	 */

	/* If one of the diffs is a conflict, just dup it */
	if (b->status == GIT_DELTA_CONFLICTED)
		return git_diff__delta_dup(b, pool);
	if (a->status == GIT_DELTA_CONFLICTED)
		return git_diff__delta_dup(a, pool);

	/* if f2 == f3 or f2 is deleted, then just dup the 'a' diff */
	if (b->status == GIT_DELTA_UNMODIFIED || a->status == GIT_DELTA_DELETED)
		return git_diff__delta_dup(a, pool);

	/* otherwise, base this diff on the 'b' diff */
	if ((dup = git_diff__delta_dup(b, pool)) == NULL)
		return NULL;

	/* If 'a' status is uninteresting, then we're done */
	if (a->status == GIT_DELTA_UNMODIFIED ||
		a->status == GIT_DELTA_UNTRACKED ||
		a->status == GIT_DELTA_UNREADABLE)
		return dup;

	assert(b->status != GIT_DELTA_UNMODIFIED);

	/* A cgit exception is that the diff of a file that is only in the
	 * index (i.e. not in HEAD nor workdir) is given as empty.
	 */
	if (dup->status == GIT_DELTA_DELETED) {
		if (a->status == GIT_DELTA_ADDED) {
			dup->status = GIT_DELTA_UNMODIFIED;
			dup->nfiles = 2;
		}
		/* else don't overwrite DELETE status */
	} else {
		dup->status = a->status;
		dup->nfiles = a->nfiles;
	}

	git_oid_cpy(&dup->old_file.id, &a->old_file.id);
	dup->old_file.mode  = a->old_file.mode;
	dup->old_file.size  = a->old_file.size;
	dup->old_file.flags = a->old_file.flags;

	return dup;
}