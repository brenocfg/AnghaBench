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
struct TYPE_13__ {int status; int /*<<< orphan*/  flags; int /*<<< orphan*/  similarity; TYPE_1__ old_file; } ;
typedef  TYPE_3__ git_diff_delta ;
struct TYPE_14__ {int /*<<< orphan*/  deltas; } ;
typedef  TYPE_4__ git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_SET (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
#define  GIT_DELTA_ADDED 135 
#define  GIT_DELTA_CONFLICTED 134 
#define  GIT_DELTA_DELETED 133 
#define  GIT_DELTA_IGNORED 132 
#define  GIT_DELTA_TYPECHANGE 131 
#define  GIT_DELTA_UNMODIFIED 130 
#define  GIT_DELTA_UNREADABLE 129 
#define  GIT_DELTA_UNTRACKED 128 
 int /*<<< orphan*/  GIT_DIFF_BREAK_REWRITES ; 
 int /*<<< orphan*/  GIT_DIFF_FIND_COPIES ; 
 int /*<<< orphan*/  GIT_DIFF_FIND_COPIES_FROM_UNMODIFIED ; 
 int /*<<< orphan*/  GIT_DIFF_FIND_REMOVE_UNMODIFIED ; 
 int /*<<< orphan*/  GIT_DIFF_FIND_RENAMES_FROM_REWRITES ; 
 int /*<<< orphan*/  GIT_DIFF_FIND_REWRITES ; 
 int /*<<< orphan*/  GIT_DIFF_FLAG__IS_RENAME_SOURCE ; 
 int /*<<< orphan*/  GIT_DIFF_FLAG__TO_DELETE ; 
 int /*<<< orphan*/  GIT_DIFF_FLAG__TO_SPLIT ; 
 int /*<<< orphan*/  GIT_MODE_ISBLOB (int /*<<< orphan*/ ) ; 
 TYPE_3__* GIT_VECTOR_GET (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  calc_self_similarity (TYPE_4__*,TYPE_2__ const*,size_t,void**) ; 

__attribute__((used)) static bool is_rename_source(
	git_diff *diff,
	const git_diff_find_options *opts,
	size_t delta_idx,
	void **cache)
{
	git_diff_delta *delta = GIT_VECTOR_GET(&diff->deltas, delta_idx);

	/* skip things that aren't blobs */
	if (!GIT_MODE_ISBLOB(delta->old_file.mode))
		return false;

	switch (delta->status) {
	case GIT_DELTA_ADDED:
	case GIT_DELTA_UNTRACKED:
	case GIT_DELTA_UNREADABLE:
	case GIT_DELTA_IGNORED:
	case GIT_DELTA_CONFLICTED:
		return false;

	case GIT_DELTA_DELETED:
	case GIT_DELTA_TYPECHANGE:
		break;

	case GIT_DELTA_UNMODIFIED:
		if (!FLAG_SET(opts, GIT_DIFF_FIND_COPIES_FROM_UNMODIFIED))
			return false;
		if (FLAG_SET(opts, GIT_DIFF_FIND_REMOVE_UNMODIFIED))
			delta->flags |= GIT_DIFF_FLAG__TO_DELETE;
		break;

	default: /* MODIFIED, RENAMED, COPIED */
		/* if we're finding copies, this could be a source */
		if (FLAG_SET(opts, GIT_DIFF_FIND_COPIES))
			break;

		/* otherwise, this is only a source if we can split it */
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
			delta->similarity < opts->rename_from_rewrite_threshold)
			break;

		return false;
	}

	delta->flags |= GIT_DIFF_FLAG__IS_RENAME_SOURCE;
	return true;
}