#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rename_conflict_info {int /*<<< orphan*/  branch1; int /*<<< orphan*/  branch2; int /*<<< orphan*/  dst_entry2; int /*<<< orphan*/  dst_entry1; TYPE_2__* pair2; TYPE_1__* pair1; } ;
struct merge_options {int call_depth; TYPE_3__* repo; } ;
struct merge_file_info {int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; } ;
struct diff_filespec {char* path; int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;
struct TYPE_5__ {struct diff_filespec* two; } ;
struct TYPE_4__ {struct diff_filespec* two; struct diff_filespec* one; } ;

/* Variables and functions */
 char* _ (char*) ; 
 struct diff_filespec* filespec_from_entry (struct diff_filespec*,int /*<<< orphan*/ ,int) ; 
 char* find_path_for_conflict (struct merge_options*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ handle_file_collision (struct merge_options*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ merge_mode_and_contents (struct merge_options*,struct diff_filespec*,struct diff_filespec*,struct diff_filespec*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct merge_file_info*) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,char*,char*,char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  remove_file_from_index (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ update_file (struct merge_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ update_stages (struct merge_options*,char*,int /*<<< orphan*/ *,struct diff_filespec*,struct diff_filespec*) ; 
 char* xstrfmt (char*,char*,char*,char*) ; 

__attribute__((used)) static int handle_rename_rename_1to2(struct merge_options *o,
				     struct rename_conflict_info *ci)
{
	/* One file was renamed in both branches, but to different names. */
	struct merge_file_info mfi;
	struct diff_filespec other;
	struct diff_filespec *add;
	struct diff_filespec *one = ci->pair1->one;
	struct diff_filespec *a = ci->pair1->two;
	struct diff_filespec *b = ci->pair2->two;
	char *path_desc;

	output(o, 1, _("CONFLICT (rename/rename): "
	       "Rename \"%s\"->\"%s\" in branch \"%s\" "
	       "rename \"%s\"->\"%s\" in \"%s\"%s"),
	       one->path, a->path, ci->branch1,
	       one->path, b->path, ci->branch2,
	       o->call_depth ? _(" (left unresolved)") : "");

	path_desc = xstrfmt("%s and %s, both renamed from %s",
			    a->path, b->path, one->path);
	if (merge_mode_and_contents(o, one, a, b, path_desc,
				    ci->branch1, ci->branch2,
				    o->call_depth * 2, &mfi))
		return -1;
	free(path_desc);

	if (o->call_depth) {
		/*
		 * FIXME: For rename/add-source conflicts (if we could detect
		 * such), this is wrong.  We should instead find a unique
		 * pathname and then either rename the add-source file to that
		 * unique path, or use that unique path instead of src here.
		 */
		if (update_file(o, 0, &mfi.oid, mfi.mode, one->path))
			return -1;

		/*
		 * Above, we put the merged content at the merge-base's
		 * path.  Now we usually need to delete both a->path and
		 * b->path.  However, the rename on each side of the merge
		 * could also be involved in a rename/add conflict.  In
		 * such cases, we should keep the added file around,
		 * resolving the conflict at that path in its favor.
		 */
		add = filespec_from_entry(&other, ci->dst_entry1, 2 ^ 1);
		if (add) {
			if (update_file(o, 0, &add->oid, add->mode, a->path))
				return -1;
		}
		else
			remove_file_from_index(o->repo->index, a->path);
		add = filespec_from_entry(&other, ci->dst_entry2, 3 ^ 1);
		if (add) {
			if (update_file(o, 0, &add->oid, add->mode, b->path))
				return -1;
		}
		else
			remove_file_from_index(o->repo->index, b->path);
	} else {
		/*
		 * For each destination path, we need to see if there is a
		 * rename/add collision.  If not, we can write the file out
		 * to the specified location.
		 */
		add = filespec_from_entry(&other, ci->dst_entry1, 2 ^ 1);
		if (add) {
			if (handle_file_collision(o, a->path,
						  NULL, NULL,
						  ci->branch1, ci->branch2,
						  &mfi.oid, mfi.mode,
						  &add->oid, add->mode) < 0)
				return -1;
		} else {
			char *new_path = find_path_for_conflict(o, a->path,
								ci->branch1,
								ci->branch2);
			if (update_file(o, 0, &mfi.oid, mfi.mode, new_path ? new_path : a->path))
				return -1;
			free(new_path);
			if (update_stages(o, a->path, NULL, a, NULL))
				return -1;
		}

		add = filespec_from_entry(&other, ci->dst_entry2, 3 ^ 1);
		if (add) {
			if (handle_file_collision(o, b->path,
						  NULL, NULL,
						  ci->branch1, ci->branch2,
						  &add->oid, add->mode,
						  &mfi.oid, mfi.mode) < 0)
				return -1;
		} else {
			char *new_path = find_path_for_conflict(o, b->path,
								ci->branch2,
								ci->branch1);
			if (update_file(o, 0, &mfi.oid, mfi.mode, new_path ? new_path : b->path))
				return -1;
			free(new_path);
			if (update_stages(o, b->path, NULL, NULL, b))
				return -1;
		}
	}

	return 0;
}