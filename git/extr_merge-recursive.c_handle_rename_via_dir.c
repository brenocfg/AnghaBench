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
struct rename_conflict_info {struct rename* ren1; } ;
struct rename {scalar_t__ branch; int /*<<< orphan*/  dir_rename_original_dest; TYPE_1__* pair; } ;
struct merge_options {scalar_t__ detect_directory_renames; scalar_t__ branch1; TYPE_2__* priv; } ;
struct diff_filespec {char* path; } ;
struct TYPE_4__ {int /*<<< orphan*/  call_depth; } ;
struct TYPE_3__ {struct diff_filespec* two; } ;

/* Variables and functions */
 scalar_t__ MERGE_DIRECTORY_RENAMES_CONFLICT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,int /*<<< orphan*/ ,char*,char*) ; 
 char* unique_path (struct merge_options*,char*,scalar_t__) ; 
 scalar_t__ update_file (struct merge_options*,int,struct diff_filespec const*,char*) ; 
 scalar_t__ update_stages (struct merge_options*,char*,int /*<<< orphan*/ *,struct diff_filespec const*,struct diff_filespec const*) ; 
 scalar_t__ would_lose_untracked (struct merge_options*,char*) ; 

__attribute__((used)) static int handle_rename_via_dir(struct merge_options *opt,
				 struct rename_conflict_info *ci)
{
	/*
	 * Handle file adds that need to be renamed due to directory rename
	 * detection.  This differs from handle_rename_normal, because
	 * there is no content merge to do; just move the file into the
	 * desired final location.
	 */
	const struct rename *ren = ci->ren1;
	const struct diff_filespec *dest = ren->pair->two;
	char *file_path = dest->path;
	int mark_conflicted = (opt->detect_directory_renames ==
			       MERGE_DIRECTORY_RENAMES_CONFLICT);
	assert(ren->dir_rename_original_dest);

	if (!opt->priv->call_depth && would_lose_untracked(opt, dest->path)) {
		mark_conflicted = 1;
		file_path = unique_path(opt, dest->path, ren->branch);
		output(opt, 1, _("Error: Refusing to lose untracked file at %s; "
				 "writing to %s instead."),
		       dest->path, file_path);
	}

	if (mark_conflicted) {
		/*
		 * Write the file in worktree at file_path.  In the index,
		 * only record the file at dest->path in the appropriate
		 * higher stage.
		 */
		if (update_file(opt, 0, dest, file_path))
			return -1;
		if (file_path != dest->path)
			free(file_path);
		if (update_stages(opt, dest->path, NULL,
				  ren->branch == opt->branch1 ? dest : NULL,
				  ren->branch == opt->branch1 ? NULL : dest))
			return -1;
		return 0; /* not clean, but conflicted */
	} else {
		/* Update dest->path both in index and in worktree */
		if (update_file(opt, 1, dest, dest->path))
			return -1;
		return 1; /* clean */
	}
}