#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  rename_from_rewrite_threshold; int /*<<< orphan*/  break_rewrite_threshold; } ;
typedef  TYPE_2__ git_diff_find_options ;
struct TYPE_11__ {int /*<<< orphan*/  mode; } ;
struct TYPE_13__ {int status; int /*<<< orphan*/  flags; int /*<<< orphan*/  similarity; TYPE_1__ new_file; } ;
typedef  TYPE_3__ git_diff_delta ;
struct TYPE_14__ {int /*<<< orphan*/  deltas; } ;
typedef  TYPE_4__ git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_SET (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
#define  GIT_DELTA_CONFLICTED 133 
#define  GIT_DELTA_DELETED 132 
#define  GIT_DELTA_IGNORED 131 
#define  GIT_DELTA_MODIFIED 130 
#define  GIT_DELTA_UNMODIFIED 129 
#define  GIT_DELTA_UNTRACKED 128 
 int /*<<< orphan*/  GIT_DIFF_BREAK_REWRITES ; 
 int /*<<< orphan*/  GIT_DIFF_FIND_FOR_UNTRACKED ; 
 int /*<<< orphan*/  GIT_DIFF_FIND_RENAMES_FROM_REWRITES ; 
 int /*<<< orphan*/  GIT_DIFF_FIND_REWRITES ; 
 int /*<<< orphan*/  GIT_DIFF_FLAG__IS_RENAME_TARGET ; 
 int /*<<< orphan*/  GIT_DIFF_FLAG__TO_SPLIT ; 
 int /*<<< orphan*/  GIT_MODE_ISBLOB (int /*<<< orphan*/ ) ; 
 TYPE_3__* GIT_VECTOR_GET (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  calc_self_similarity (TYPE_4__*,TYPE_2__ const*,size_t,void**) ; 

__attribute__((used)) static bool is_rename_target(
	git_diff *diff,
	const git_diff_find_options *opts,
	size_t delta_idx,
	void **cache)
{
	git_diff_delta *delta = GIT_VECTOR_GET(&diff->deltas, delta_idx);

	/* skip things that aren't plain blobs */
	if (!GIT_MODE_ISBLOB(delta->new_file.mode))
		return false;

	/* only consider ADDED, RENAMED, COPIED, and split MODIFIED as
	 * targets; maybe include UNTRACKED if requested.
	 */
	switch (delta->status) {
	case GIT_DELTA_UNMODIFIED:
	case GIT_DELTA_DELETED:
	case GIT_DELTA_IGNORED:
	case GIT_DELTA_CONFLICTED:
		return false;

	case GIT_DELTA_MODIFIED:
		if (!FLAG_SET(opts, GIT_DIFF_FIND_REWRITES) &&
			!FLAG_SET(opts, GIT_DIFF_FIND_RENAMES_FROM_REWRITES))
			return false;

		if (calc_self_similarity(diff, opts, delta_idx, cache) < 0)
			return false;

		if (FLAG_SET(opts, GIT_DIFF_BREAK_REWRITES) &&
			delta->similarity < opts->break_rewrite_threshold) {
			delta->flags |= GIT_DIFF_FLAG__TO_SPLIT;
			break;
		}
		if (FLAG_SET(opts, GIT_DIFF_FIND_RENAMES_FROM_REWRITES) &&
			delta->similarity < opts->rename_from_rewrite_threshold) {
			delta->flags |= GIT_DIFF_FLAG__TO_SPLIT;
			break;
		}

		return false;

	case GIT_DELTA_UNTRACKED:
		if (!FLAG_SET(opts, GIT_DIFF_FIND_FOR_UNTRACKED))
			return false;
		break;

	default: /* all other status values should be checked */
		break;
	}

	delta->flags |= GIT_DIFF_FLAG__IS_RENAME_TARGET;
	return true;
}