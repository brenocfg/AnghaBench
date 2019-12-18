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
struct merge_options {char const* branch1; TYPE_2__* repo; TYPE_1__* priv; } ;
struct diff_filespec {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;
struct TYPE_3__ {scalar_t__ call_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ dir_in_way (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,char const*,char const*,char const*,...) ; 
 int remove_file_from_index (int /*<<< orphan*/ ,char const*) ; 
 char* unique_path (struct merge_options*,char const*,char const*) ; 
 int update_file (struct merge_options*,int /*<<< orphan*/ ,struct diff_filespec const*,char const*) ; 
 scalar_t__ would_lose_untracked (struct merge_options*,char const*) ; 

__attribute__((used)) static int handle_change_delete(struct merge_options *opt,
				const char *path, const char *old_path,
				const struct diff_filespec *o,
				const struct diff_filespec *changed,
				const char *change_branch,
				const char *delete_branch,
				const char *change, const char *change_past)
{
	char *alt_path = NULL;
	const char *update_path = path;
	int ret = 0;

	if (dir_in_way(opt->repo->index, path, !opt->priv->call_depth, 0) ||
	    (!opt->priv->call_depth && would_lose_untracked(opt, path))) {
		update_path = alt_path = unique_path(opt, path, change_branch);
	}

	if (opt->priv->call_depth) {
		/*
		 * We cannot arbitrarily accept either a_sha or b_sha as
		 * correct; since there is no true "middle point" between
		 * them, simply reuse the base version for virtual merge base.
		 */
		ret = remove_file_from_index(opt->repo->index, path);
		if (!ret)
			ret = update_file(opt, 0, o, update_path);
	} else {
		/*
		 * Despite the four nearly duplicate messages and argument
		 * lists below and the ugliness of the nested if-statements,
		 * having complete messages makes the job easier for
		 * translators.
		 *
		 * The slight variance among the cases is due to the fact
		 * that:
		 *   1) directory/file conflicts (in effect if
		 *      !alt_path) could cause us to need to write the
		 *      file to a different path.
		 *   2) renames (in effect if !old_path) could mean that
		 *      there are two names for the path that the user
		 *      may know the file by.
		 */
		if (!alt_path) {
			if (!old_path) {
				output(opt, 1, _("CONFLICT (%s/delete): %s deleted in %s "
				       "and %s in %s. Version %s of %s left in tree."),
				       change, path, delete_branch, change_past,
				       change_branch, change_branch, path);
			} else {
				output(opt, 1, _("CONFLICT (%s/delete): %s deleted in %s "
				       "and %s to %s in %s. Version %s of %s left in tree."),
				       change, old_path, delete_branch, change_past, path,
				       change_branch, change_branch, path);
			}
		} else {
			if (!old_path) {
				output(opt, 1, _("CONFLICT (%s/delete): %s deleted in %s "
				       "and %s in %s. Version %s of %s left in tree at %s."),
				       change, path, delete_branch, change_past,
				       change_branch, change_branch, path, alt_path);
			} else {
				output(opt, 1, _("CONFLICT (%s/delete): %s deleted in %s "
				       "and %s to %s in %s. Version %s of %s left in tree at %s."),
				       change, old_path, delete_branch, change_past, path,
				       change_branch, change_branch, path, alt_path);
			}
		}
		/*
		 * No need to call update_file() on path when change_branch ==
		 * opt->branch1 && !alt_path, since that would needlessly touch
		 * path.  We could call update_file_flags() with update_cache=0
		 * and update_wd=0, but that's a no-op.
		 */
		if (change_branch != opt->branch1 || alt_path)
			ret = update_file(opt, 0, changed, update_path);
	}
	free(alt_path);

	return ret;
}