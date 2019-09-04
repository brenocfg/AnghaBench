#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_pool ;
struct TYPE_10__ {scalar_t__ status; } ;
typedef  TYPE_1__ git_diff_delta ;

/* Variables and functions */
 scalar_t__ GIT_DELTA_DELETED ; 
 scalar_t__ GIT_DELTA_MODIFIED ; 
 scalar_t__ GIT_DELTA_UNTRACKED ; 
 TYPE_1__* git_diff__delta_dup (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* git_diff__merge_like_cgit (TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static git_diff_delta *stash_delta_merge(
	const git_diff_delta *a,
	const git_diff_delta *b,
	git_pool *pool)
{
	/* Special case for stash: if a file is deleted in the index, but exists
	 * in the working tree, we need to stash the workdir copy for the workdir.
	 */
	if (a->status == GIT_DELTA_DELETED && b->status == GIT_DELTA_UNTRACKED) {
		git_diff_delta *dup = git_diff__delta_dup(b, pool);

		if (dup)
			dup->status = GIT_DELTA_MODIFIED;
		return dup;
	}

	return git_diff__merge_like_cgit(a, b, pool);
}