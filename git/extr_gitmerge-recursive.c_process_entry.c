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
struct stage_data {int processed; struct rename_conflict_info* rename_conflict_info; TYPE_1__* stages; } ;
struct rename_conflict_info {int rename_type; int /*<<< orphan*/  branch2; int /*<<< orphan*/  branch1; int /*<<< orphan*/  pair1; } ;
struct object_id {int dummy; } ;
struct merge_options {int renormalize; char* branch1; char* branch2; TYPE_2__* repo; scalar_t__ call_depth; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;
struct TYPE_3__ {unsigned int mode; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
#define  RENAME_ADD 134 
#define  RENAME_DELETE 133 
#define  RENAME_NORMAL 132 
#define  RENAME_ONE_FILE_TO_ONE 131 
#define  RENAME_ONE_FILE_TO_TWO 130 
#define  RENAME_TWO_FILES_TO_ONE 129 
#define  RENAME_VIA_DIR 128 
 int /*<<< orphan*/  S_ISGITLINK (unsigned int) ; 
 char* _ (char*) ; 
 scalar_t__ blob_unchanged (struct merge_options*,struct object_id*,unsigned int,struct object_id*,unsigned int,int,char const*) ; 
 scalar_t__ dir_in_way (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int handle_content_merge (struct merge_options*,char const*,int,struct object_id*,unsigned int,struct object_id*,unsigned int,struct object_id*,unsigned int,int /*<<< orphan*/ *) ; 
 int handle_file_collision (struct merge_options*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,struct object_id*,unsigned int,struct object_id*,unsigned int) ; 
 scalar_t__ handle_modify_delete (struct merge_options*,char const*,struct object_id*,unsigned int,struct object_id*,unsigned int,struct object_id*,unsigned int) ; 
 int handle_rename_add (struct merge_options*,struct rename_conflict_info*) ; 
 int /*<<< orphan*/  handle_rename_delete (struct merge_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int handle_rename_normal (struct merge_options*,char const*,struct object_id*,unsigned int,struct object_id*,unsigned int,struct object_id*,unsigned int,struct rename_conflict_info*) ; 
 int /*<<< orphan*/  handle_rename_rename_1to2 (struct merge_options*,struct rename_conflict_info*) ; 
 int handle_rename_rename_2to1 (struct merge_options*,struct rename_conflict_info*) ; 
 int /*<<< orphan*/  handle_rename_via_dir (struct merge_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  remove_file (struct merge_options*,int,char const*,int) ; 
 int /*<<< orphan*/  remove_file_from_index (int /*<<< orphan*/ ,char const*) ; 
 struct object_id* stage_oid (int /*<<< orphan*/ *,unsigned int) ; 
 char* unique_path (struct merge_options*,char const*,char const*) ; 
 scalar_t__ update_file (struct merge_options*,int /*<<< orphan*/ ,struct object_id const*,unsigned int,char*) ; 
 scalar_t__ update_file_flags (struct merge_options*,struct object_id const*,unsigned int,char const*,int,int) ; 

__attribute__((used)) static int process_entry(struct merge_options *o,
			 const char *path, struct stage_data *entry)
{
	int clean_merge = 1;
	int normalize = o->renormalize;
	unsigned o_mode = entry->stages[1].mode;
	unsigned a_mode = entry->stages[2].mode;
	unsigned b_mode = entry->stages[3].mode;
	struct object_id *o_oid = stage_oid(&entry->stages[1].oid, o_mode);
	struct object_id *a_oid = stage_oid(&entry->stages[2].oid, a_mode);
	struct object_id *b_oid = stage_oid(&entry->stages[3].oid, b_mode);

	entry->processed = 1;
	if (entry->rename_conflict_info) {
		struct rename_conflict_info *conflict_info = entry->rename_conflict_info;
		switch (conflict_info->rename_type) {
		case RENAME_NORMAL:
		case RENAME_ONE_FILE_TO_ONE:
			clean_merge = handle_rename_normal(o,
							   path,
							   o_oid, o_mode,
							   a_oid, a_mode,
							   b_oid, b_mode,
							   conflict_info);
			break;
		case RENAME_VIA_DIR:
			clean_merge = 1;
			if (handle_rename_via_dir(o,
						  conflict_info->pair1,
						  conflict_info->branch1))
				clean_merge = -1;
			break;
		case RENAME_ADD:
			/*
			 * Probably unclean merge, but if the renamed file
			 * merges cleanly and the result can then be
			 * two-way merged cleanly with the added file, I
			 * guess it's a clean merge?
			 */
			clean_merge = handle_rename_add(o, conflict_info);
			break;
		case RENAME_DELETE:
			clean_merge = 0;
			if (handle_rename_delete(o,
						 conflict_info->pair1,
						 conflict_info->branch1,
						 conflict_info->branch2))
				clean_merge = -1;
			break;
		case RENAME_ONE_FILE_TO_TWO:
			clean_merge = 0;
			if (handle_rename_rename_1to2(o, conflict_info))
				clean_merge = -1;
			break;
		case RENAME_TWO_FILES_TO_ONE:
			/*
			 * Probably unclean merge, but if the two renamed
			 * files merge cleanly and the two resulting files
			 * can then be two-way merged cleanly, I guess it's
			 * a clean merge?
			 */
			clean_merge = handle_rename_rename_2to1(o,
								conflict_info);
			break;
		default:
			entry->processed = 0;
			break;
		}
	} else if (o_oid && (!a_oid || !b_oid)) {
		/* Case A: Deleted in one */
		if ((!a_oid && !b_oid) ||
		    (!b_oid && blob_unchanged(o, o_oid, o_mode, a_oid, a_mode, normalize, path)) ||
		    (!a_oid && blob_unchanged(o, o_oid, o_mode, b_oid, b_mode, normalize, path))) {
			/* Deleted in both or deleted in one and
			 * unchanged in the other */
			if (a_oid)
				output(o, 2, _("Removing %s"), path);
			/* do not touch working file if it did not exist */
			remove_file(o, 1, path, !a_oid);
		} else {
			/* Modify/delete; deleted side may have put a directory in the way */
			clean_merge = 0;
			if (handle_modify_delete(o, path, o_oid, o_mode,
						 a_oid, a_mode, b_oid, b_mode))
				clean_merge = -1;
		}
	} else if ((!o_oid && a_oid && !b_oid) ||
		   (!o_oid && !a_oid && b_oid)) {
		/* Case B: Added in one. */
		/* [nothing|directory] -> ([nothing|directory], file) */

		const char *add_branch;
		const char *other_branch;
		unsigned mode;
		const struct object_id *oid;
		const char *conf;

		if (a_oid) {
			add_branch = o->branch1;
			other_branch = o->branch2;
			mode = a_mode;
			oid = a_oid;
			conf = _("file/directory");
		} else {
			add_branch = o->branch2;
			other_branch = o->branch1;
			mode = b_mode;
			oid = b_oid;
			conf = _("directory/file");
		}
		if (dir_in_way(o->repo->index, path,
			       !o->call_depth && !S_ISGITLINK(a_mode),
			       0)) {
			char *new_path = unique_path(o, path, add_branch);
			clean_merge = 0;
			output(o, 1, _("CONFLICT (%s): There is a directory with name %s in %s. "
			       "Adding %s as %s"),
			       conf, path, other_branch, path, new_path);
			if (update_file(o, 0, oid, mode, new_path))
				clean_merge = -1;
			else if (o->call_depth)
				remove_file_from_index(o->repo->index, path);
			free(new_path);
		} else {
			output(o, 2, _("Adding %s"), path);
			/* do not overwrite file if already present */
			if (update_file_flags(o, oid, mode, path, 1, !a_oid))
				clean_merge = -1;
		}
	} else if (a_oid && b_oid) {
		if (!o_oid) {
			/* Case C: Added in both (check for same permissions) */
			output(o, 1,
			       _("CONFLICT (add/add): Merge conflict in %s"),
			       path);
			clean_merge = handle_file_collision(o,
							    path, NULL, NULL,
							    o->branch1,
							    o->branch2,
							    a_oid, a_mode,
							    b_oid, b_mode);
		} else {
			/* case D: Modified in both, but differently. */
			int is_dirty = 0; /* unpack_trees would have bailed if dirty */
			clean_merge = handle_content_merge(o, path,
							   is_dirty,
							   o_oid, o_mode,
							   a_oid, a_mode,
							   b_oid, b_mode,
							   NULL);
		}
	} else if (!o_oid && !a_oid && !b_oid) {
		/*
		 * this entry was deleted altogether. a_mode == 0 means
		 * we had that path and want to actively remove it.
		 */
		remove_file(o, 1, path, !a_mode);
	} else
		BUG("fatal merge failure, shouldn't happen.");

	return clean_merge;
}