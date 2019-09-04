#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct merge_options {char const* branch1; TYPE_1__* repo; scalar_t__ call_depth; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ dir_in_way (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,char const*,char const*,char const*,...) ; 
 int remove_file_from_index (int /*<<< orphan*/ ,char const*) ; 
 char* unique_path (struct merge_options*,char const*,char const*) ; 
 int update_file (struct merge_options*,int /*<<< orphan*/ ,struct object_id const*,int,char const*) ; 
 scalar_t__ would_lose_untracked (struct merge_options*,char const*) ; 

__attribute__((used)) static int handle_change_delete(struct merge_options *o,
				const char *path, const char *old_path,
				const struct object_id *o_oid, int o_mode,
				const struct object_id *changed_oid,
				int changed_mode,
				const char *change_branch,
				const char *delete_branch,
				const char *change, const char *change_past)
{
	char *alt_path = NULL;
	const char *update_path = path;
	int ret = 0;

	if (dir_in_way(o->repo->index, path, !o->call_depth, 0) ||
	    (!o->call_depth && would_lose_untracked(o, path))) {
		update_path = alt_path = unique_path(o, path, change_branch);
	}

	if (o->call_depth) {
		/*
		 * We cannot arbitrarily accept either a_sha or b_sha as
		 * correct; since there is no true "middle point" between
		 * them, simply reuse the base version for virtual merge base.
		 */
		ret = remove_file_from_index(o->repo->index, path);
		if (!ret)
			ret = update_file(o, 0, o_oid, o_mode, update_path);
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
				output(o, 1, _("CONFLICT (%s/delete): %s deleted in %s "
				       "and %s in %s. Version %s of %s left in tree."),
				       change, path, delete_branch, change_past,
				       change_branch, change_branch, path);
			} else {
				output(o, 1, _("CONFLICT (%s/delete): %s deleted in %s "
				       "and %s to %s in %s. Version %s of %s left in tree."),
				       change, old_path, delete_branch, change_past, path,
				       change_branch, change_branch, path);
			}
		} else {
			if (!old_path) {
				output(o, 1, _("CONFLICT (%s/delete): %s deleted in %s "
				       "and %s in %s. Version %s of %s left in tree at %s."),
				       change, path, delete_branch, change_past,
				       change_branch, change_branch, path, alt_path);
			} else {
				output(o, 1, _("CONFLICT (%s/delete): %s deleted in %s "
				       "and %s to %s in %s. Version %s of %s left in tree at %s."),
				       change, old_path, delete_branch, change_past, path,
				       change_branch, change_branch, path, alt_path);
			}
		}
		/*
		 * No need to call update_file() on path when change_branch ==
		 * o->branch1 && !alt_path, since that would needlessly touch
		 * path.  We could call update_file_flags() with update_cache=0
		 * and update_wd=0, but that's a no-op.
		 */
		if (change_branch != o->branch1 || alt_path)
			ret = update_file(o, 0, changed_oid, changed_mode, update_path);
	}
	free(alt_path);

	return ret;
}