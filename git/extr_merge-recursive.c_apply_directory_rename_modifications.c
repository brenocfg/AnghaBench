#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
struct tree {TYPE_1__ object; } ;
struct string_list_item {TYPE_4__* util; } ;
struct string_list {int dummy; } ;
struct rename {char dir_rename_original_type; char* dir_rename_original_dest; TYPE_4__* dst_entry; } ;
struct merge_options {int /*<<< orphan*/  repo; } ;
struct diff_filepair {char status; TYPE_3__* two; } ;
struct TYPE_8__ {int processed; TYPE_2__* stages; } ;
struct TYPE_7__ {char* path; } ;
struct TYPE_6__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  get_tree_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* insert_stage_data (int /*<<< orphan*/ ,char*,struct tree*,struct tree*,struct tree*,struct string_list*) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  remove_file (struct merge_options*,int,char*,int) ; 
 struct string_list_item* string_list_insert (struct string_list*,char*) ; 
 struct string_list_item* string_list_lookup (struct string_list*,char*) ; 
 int /*<<< orphan*/  was_dirty (struct merge_options*,char*) ; 

__attribute__((used)) static void apply_directory_rename_modifications(struct merge_options *opt,
						 struct diff_filepair *pair,
						 char *new_path,
						 struct rename *re,
						 struct tree *tree,
						 struct tree *o_tree,
						 struct tree *a_tree,
						 struct tree *b_tree,
						 struct string_list *entries)
{
	struct string_list_item *item;
	int stage = (tree == a_tree ? 2 : 3);
	int update_wd;

	/*
	 * In all cases where we can do directory rename detection,
	 * unpack_trees() will have read pair->two->path into the
	 * index and the working copy.  We need to remove it so that
	 * we can instead place it at new_path.  It is guaranteed to
	 * not be untracked (unpack_trees() would have errored out
	 * saying the file would have been overwritten), but it might
	 * be dirty, though.
	 */
	update_wd = !was_dirty(opt, pair->two->path);
	if (!update_wd)
		output(opt, 1, _("Refusing to lose dirty file at %s"),
		       pair->two->path);
	remove_file(opt, 1, pair->two->path, !update_wd);

	/* Find or create a new re->dst_entry */
	item = string_list_lookup(entries, new_path);
	if (item) {
		/*
		 * Since we're renaming on this side of history, and it's
		 * due to a directory rename on the other side of history
		 * (which we only allow when the directory in question no
		 * longer exists on the other side of history), the
		 * original entry for re->dst_entry is no longer
		 * necessary...
		 */
		re->dst_entry->processed = 1;

		/*
		 * ...because we'll be using this new one.
		 */
		re->dst_entry = item->util;
	} else {
		/*
		 * re->dst_entry is for the before-dir-rename path, and we
		 * need it to hold information for the after-dir-rename
		 * path.  Before creating a new entry, we need to mark the
		 * old one as unnecessary (...unless it is shared by
		 * src_entry, i.e. this didn't use to be a rename, in which
		 * case we can just allow the normal processing to happen
		 * for it).
		 */
		if (pair->status == 'R')
			re->dst_entry->processed = 1;

		re->dst_entry = insert_stage_data(opt->repo, new_path,
						  o_tree, a_tree, b_tree,
						  entries);
		item = string_list_insert(entries, new_path);
		item->util = re->dst_entry;
	}

	/*
	 * Update the stage_data with the information about the path we are
	 * moving into place.  That slot will be empty and available for us
	 * to write to because of the collision checks in
	 * handle_path_level_conflicts().  In other words,
	 * re->dst_entry->stages[stage].oid will be the null_oid, so it's
	 * open for us to write to.
	 *
	 * It may be tempting to actually update the index at this point as
	 * well, using update_stages_for_stage_data(), but as per the big
	 * "NOTE" in update_stages(), doing so will modify the current
	 * in-memory index which will break calls to would_lose_untracked()
	 * that we need to make.  Instead, we need to just make sure that
	 * the various handle_rename_*() functions update the index
	 * explicitly rather than relying on unpack_trees() to have done it.
	 */
	get_tree_entry(opt->repo,
		       &tree->object.oid,
		       pair->two->path,
		       &re->dst_entry->stages[stage].oid,
		       &re->dst_entry->stages[stage].mode);

	/*
	 * Record the original change status (or 'type' of change).  If it
	 * was originally an add ('A'), this lets us differentiate later
	 * between a RENAME_DELETE conflict and RENAME_VIA_DIR (they
	 * otherwise look the same).  If it was originally a rename ('R'),
	 * this lets us remember and report accurately about the transitive
	 * renaming that occurred via the directory rename detection.  Also,
	 * record the original destination name.
	 */
	re->dir_rename_original_type = pair->status;
	re->dir_rename_original_dest = pair->two->path;

	/*
	 * We don't actually look at pair->status again, but it seems
	 * pedagogically correct to adjust it.
	 */
	pair->status = 'R';

	/*
	 * Finally, record the new location.
	 */
	pair->two->path = new_path;
}