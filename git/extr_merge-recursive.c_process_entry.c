#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct stage_data {int processed; struct rename_conflict_info* rename_conflict_info; struct diff_filespec* stages; } ;
struct rename_conflict_info {int rename_type; TYPE_6__* ren2; TYPE_6__* ren1; } ;
struct merge_options {int renormalize; scalar_t__ branch1; char* branch2; TYPE_2__* repo; TYPE_1__* priv; } ;
struct merge_file_info {int dummy; } ;
struct diff_filespec {char* path; int /*<<< orphan*/  mode; } ;
struct TYPE_12__ {scalar_t__ branch; TYPE_5__* pair; } ;
struct TYPE_11__ {TYPE_4__* two; TYPE_3__* one; } ;
struct TYPE_10__ {char* path; } ;
struct TYPE_9__ {char* path; } ;
struct TYPE_8__ {int /*<<< orphan*/  index; } ;
struct TYPE_7__ {scalar_t__ call_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
#define  RENAME_ADD 134 
#define  RENAME_DELETE 133 
#define  RENAME_NORMAL 132 
#define  RENAME_ONE_FILE_TO_ONE 131 
#define  RENAME_ONE_FILE_TO_TWO 130 
#define  RENAME_TWO_FILES_TO_ONE 129 
#define  RENAME_VIA_DIR 128 
 int /*<<< orphan*/  S_ISGITLINK (int /*<<< orphan*/ ) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ blob_unchanged (struct merge_options*,struct diff_filespec*,struct diff_filespec*,int,char const*) ; 
 scalar_t__ dir_in_way (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int handle_content_merge (struct merge_file_info*,struct merge_options*,char const*,int,struct diff_filespec*,struct diff_filespec*,struct diff_filespec*,int /*<<< orphan*/ *) ; 
 int handle_file_collision (struct merge_options*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,struct diff_filespec*,struct diff_filespec*) ; 
 scalar_t__ handle_modify_delete (struct merge_options*,char const*,struct diff_filespec*,struct diff_filespec*,struct diff_filespec*) ; 
 int handle_rename_add (struct merge_options*,struct rename_conflict_info*) ; 
 int /*<<< orphan*/  handle_rename_delete (struct merge_options*,struct rename_conflict_info*) ; 
 int handle_rename_normal (struct merge_options*,char const*,struct diff_filespec*,struct diff_filespec*,struct diff_filespec*,struct rename_conflict_info*) ; 
 int /*<<< orphan*/  handle_rename_rename_1to2 (struct merge_options*,struct rename_conflict_info*) ; 
 int handle_rename_rename_2to1 (struct merge_options*,struct rename_conflict_info*) ; 
 int handle_rename_via_dir (struct merge_options*,struct rename_conflict_info*) ; 
 int is_valid (struct diff_filespec*) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  remove_file (struct merge_options*,int,char const*,int) ; 
 int /*<<< orphan*/  remove_file_from_index (int /*<<< orphan*/ ,char const*) ; 
 char* unique_path (struct merge_options*,char const*,char const*) ; 
 scalar_t__ update_file (struct merge_options*,int /*<<< orphan*/ ,struct diff_filespec const*,char*) ; 
 scalar_t__ update_file_flags (struct merge_options*,struct diff_filespec const*,char const*,int,int) ; 
 int warn_about_dir_renamed_entries (struct merge_options*,TYPE_6__*) ; 

__attribute__((used)) static int process_entry(struct merge_options *opt,
			 const char *path, struct stage_data *entry)
{
	int clean_merge = 1;
	int normalize = opt->renormalize;

	struct diff_filespec *o = &entry->stages[1];
	struct diff_filespec *a = &entry->stages[2];
	struct diff_filespec *b = &entry->stages[3];
	int o_valid = is_valid(o);
	int a_valid = is_valid(a);
	int b_valid = is_valid(b);
	o->path = a->path = b->path = (char*)path;

	entry->processed = 1;
	if (entry->rename_conflict_info) {
		struct rename_conflict_info *ci = entry->rename_conflict_info;
		struct diff_filespec *temp;
		int path_clean;

		path_clean = warn_about_dir_renamed_entries(opt, ci->ren1);
		path_clean &= warn_about_dir_renamed_entries(opt, ci->ren2);

		/*
		 * For cases with a single rename, {o,a,b}->path have all been
		 * set to the rename target path; we need to set two of these
		 * back to the rename source.
		 * For rename/rename conflicts, we'll manually fix paths below.
		 */
		temp = (opt->branch1 == ci->ren1->branch) ? b : a;
		o->path = temp->path = ci->ren1->pair->one->path;
		if (ci->ren2) {
			assert(opt->branch1 == ci->ren1->branch);
		}

		switch (ci->rename_type) {
		case RENAME_NORMAL:
		case RENAME_ONE_FILE_TO_ONE:
			clean_merge = handle_rename_normal(opt, path, o, a, b,
							   ci);
			break;
		case RENAME_VIA_DIR:
			clean_merge = handle_rename_via_dir(opt, ci);
			break;
		case RENAME_ADD:
			/*
			 * Probably unclean merge, but if the renamed file
			 * merges cleanly and the result can then be
			 * two-way merged cleanly with the added file, I
			 * guess it's a clean merge?
			 */
			clean_merge = handle_rename_add(opt, ci);
			break;
		case RENAME_DELETE:
			clean_merge = 0;
			if (handle_rename_delete(opt, ci))
				clean_merge = -1;
			break;
		case RENAME_ONE_FILE_TO_TWO:
			/*
			 * Manually fix up paths; note:
			 * ren[12]->pair->one->path are equal.
			 */
			o->path = ci->ren1->pair->one->path;
			a->path = ci->ren1->pair->two->path;
			b->path = ci->ren2->pair->two->path;

			clean_merge = 0;
			if (handle_rename_rename_1to2(opt, ci))
				clean_merge = -1;
			break;
		case RENAME_TWO_FILES_TO_ONE:
			/*
			 * Manually fix up paths; note,
			 * ren[12]->pair->two->path are actually equal.
			 */
			o->path = NULL;
			a->path = ci->ren1->pair->two->path;
			b->path = ci->ren2->pair->two->path;

			/*
			 * Probably unclean merge, but if the two renamed
			 * files merge cleanly and the two resulting files
			 * can then be two-way merged cleanly, I guess it's
			 * a clean merge?
			 */
			clean_merge = handle_rename_rename_2to1(opt, ci);
			break;
		default:
			entry->processed = 0;
			break;
		}
		if (path_clean < clean_merge)
			clean_merge = path_clean;
	} else if (o_valid && (!a_valid || !b_valid)) {
		/* Case A: Deleted in one */
		if ((!a_valid && !b_valid) ||
		    (!b_valid && blob_unchanged(opt, o, a, normalize, path)) ||
		    (!a_valid && blob_unchanged(opt, o, b, normalize, path))) {
			/* Deleted in both or deleted in one and
			 * unchanged in the other */
			if (a_valid)
				output(opt, 2, _("Removing %s"), path);
			/* do not touch working file if it did not exist */
			remove_file(opt, 1, path, !a_valid);
		} else {
			/* Modify/delete; deleted side may have put a directory in the way */
			clean_merge = 0;
			if (handle_modify_delete(opt, path, o, a, b))
				clean_merge = -1;
		}
	} else if ((!o_valid && a_valid && !b_valid) ||
		   (!o_valid && !a_valid && b_valid)) {
		/* Case B: Added in one. */
		/* [nothing|directory] -> ([nothing|directory], file) */

		const char *add_branch;
		const char *other_branch;
		const char *conf;
		const struct diff_filespec *contents;

		if (a_valid) {
			add_branch = opt->branch1;
			other_branch = opt->branch2;
			contents = a;
			conf = _("file/directory");
		} else {
			add_branch = opt->branch2;
			other_branch = opt->branch1;
			contents = b;
			conf = _("directory/file");
		}
		if (dir_in_way(opt->repo->index, path,
			       !opt->priv->call_depth && !S_ISGITLINK(a->mode),
			       0)) {
			char *new_path = unique_path(opt, path, add_branch);
			clean_merge = 0;
			output(opt, 1, _("CONFLICT (%s): There is a directory with name %s in %s. "
			       "Adding %s as %s"),
			       conf, path, other_branch, path, new_path);
			if (update_file(opt, 0, contents, new_path))
				clean_merge = -1;
			else if (opt->priv->call_depth)
				remove_file_from_index(opt->repo->index, path);
			free(new_path);
		} else {
			output(opt, 2, _("Adding %s"), path);
			/* do not overwrite file if already present */
			if (update_file_flags(opt, contents, path, 1, !a_valid))
				clean_merge = -1;
		}
	} else if (a_valid && b_valid) {
		if (!o_valid) {
			/* Case C: Added in both (check for same permissions) */
			output(opt, 1,
			       _("CONFLICT (add/add): Merge conflict in %s"),
			       path);
			clean_merge = handle_file_collision(opt,
							    path, NULL, NULL,
							    opt->branch1,
							    opt->branch2,
							    a, b);
		} else {
			/* case D: Modified in both, but differently. */
			struct merge_file_info mfi;
			int is_dirty = 0; /* unpack_trees would have bailed if dirty */
			clean_merge = handle_content_merge(&mfi, opt, path,
							   is_dirty,
							   o, a, b, NULL);
		}
	} else if (!o_valid && !a_valid && !b_valid) {
		/*
		 * this entry was deleted altogether. a_mode == 0 means
		 * we had that path and want to actively remove it.
		 */
		remove_file(opt, 1, path, !a->mode);
	} else
		BUG("fatal merge failure, shouldn't happen.");

	return clean_merge;
}