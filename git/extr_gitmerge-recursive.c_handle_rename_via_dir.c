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
struct merge_options {char const* branch1; int /*<<< orphan*/  call_depth; } ;
struct diff_filespec {char* path; int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; } ;
struct diff_filepair {struct diff_filespec* two; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,int /*<<< orphan*/ ,char*,char*) ; 
 char* unique_path (struct merge_options*,char*,char const*) ; 
 scalar_t__ update_file (struct merge_options*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int update_stages (struct merge_options*,char*,int /*<<< orphan*/ *,struct diff_filespec const*,struct diff_filespec const*) ; 
 scalar_t__ would_lose_untracked (struct merge_options*,char*) ; 

__attribute__((used)) static int handle_rename_via_dir(struct merge_options *o,
				 struct diff_filepair *pair,
				 const char *rename_branch)
{
	/*
	 * Handle file adds that need to be renamed due to directory rename
	 * detection.  This differs from handle_rename_normal, because
	 * there is no content merge to do; just move the file into the
	 * desired final location.
	 */
	const struct diff_filespec *dest = pair->two;

	if (!o->call_depth && would_lose_untracked(o, dest->path)) {
		char *alt_path = unique_path(o, dest->path, rename_branch);

		output(o, 1, _("Error: Refusing to lose untracked file at %s; "
			       "writing to %s instead."),
		       dest->path, alt_path);
		/*
		 * Write the file in worktree at alt_path, but not in the
		 * index.  Instead, write to dest->path for the index but
		 * only at the higher appropriate stage.
		 */
		if (update_file(o, 0, &dest->oid, dest->mode, alt_path))
			return -1;
		free(alt_path);
		return update_stages(o, dest->path, NULL,
				     rename_branch == o->branch1 ? dest : NULL,
				     rename_branch == o->branch1 ? NULL : dest);
	}

	/* Update dest->path both in index and in worktree */
	if (update_file(o, 1, &dest->oid, dest->mode, dest->path))
		return -1;
	return 0;
}