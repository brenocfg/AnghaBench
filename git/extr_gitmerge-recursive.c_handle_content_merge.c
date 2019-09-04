#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rename_conflict_info {scalar_t__ branch1; scalar_t__ pair2; struct diff_filepair* pair1; } ;
struct object_id {int dummy; } ;
struct TYPE_10__ {struct cache_entry** cache; } ;
struct merge_options {scalar_t__ branch1; scalar_t__ branch2; int call_depth; TYPE_3__* repo; TYPE_4__ orig_index; } ;
struct merge_file_info {int clean; int mode; struct object_id oid; } ;
struct diff_filespec {char* path; int mode; int /*<<< orphan*/  oid; } ;
struct diff_filepair {TYPE_2__* two; TYPE_1__* one; } ;
struct cache_entry {int /*<<< orphan*/  ce_flags; } ;
struct TYPE_9__ {TYPE_4__* index; } ;
struct TYPE_8__ {char* path; int mode; } ;
struct TYPE_7__ {char* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_SKIP_WORKTREE ; 
 scalar_t__ S_ISGITLINK (int) ; 
 char* _ (char*) ; 
 scalar_t__ add_cacheinfo (struct merge_options*,int,struct object_id*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ce_skip_worktree (struct cache_entry*) ; 
 scalar_t__ dir_in_way (TYPE_4__*,char const*,int,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int index_name_pos (TYPE_4__*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ merge_mode_and_contents (struct merge_options*,struct diff_filespec*,struct diff_filespec*,struct diff_filespec*,char const*,scalar_t__,scalar_t__,int,struct merge_file_info*) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  remove_file_from_index (TYPE_4__*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* unique_path (struct merge_options*,char const*,scalar_t__) ; 
 scalar_t__ update_file (struct merge_options*,int,struct object_id*,int,char const*) ; 
 scalar_t__ update_stages (struct merge_options*,char const*,struct diff_filespec*,struct diff_filespec*,struct diff_filespec*) ; 
 int was_tracked (struct merge_options*,char const*) ; 
 scalar_t__ was_tracked_and_matches (struct merge_options*,char const*,struct object_id*,int) ; 

__attribute__((used)) static int handle_content_merge(struct merge_options *o,
				const char *path,
				int is_dirty,
				struct object_id *o_oid, int o_mode,
				struct object_id *a_oid, int a_mode,
				struct object_id *b_oid, int b_mode,
				struct rename_conflict_info *rename_conflict_info)
{
	const char *reason = _("content");
	const char *path1 = NULL, *path2 = NULL;
	struct merge_file_info mfi;
	struct diff_filespec one, a, b;
	unsigned df_conflict_remains = 0;

	if (!o_oid) {
		reason = _("add/add");
		o_oid = (struct object_id *)&null_oid;
	}
	one.path = a.path = b.path = (char *)path;
	oidcpy(&one.oid, o_oid);
	one.mode = o_mode;
	oidcpy(&a.oid, a_oid);
	a.mode = a_mode;
	oidcpy(&b.oid, b_oid);
	b.mode = b_mode;

	if (rename_conflict_info) {
		struct diff_filepair *pair1 = rename_conflict_info->pair1;

		path1 = (o->branch1 == rename_conflict_info->branch1) ?
			pair1->two->path : pair1->one->path;
		/* If rename_conflict_info->pair2 != NULL, we are in
		 * RENAME_ONE_FILE_TO_ONE case.  Otherwise, we have a
		 * normal rename.
		 */
		path2 = (rename_conflict_info->pair2 ||
			 o->branch2 == rename_conflict_info->branch1) ?
			pair1->two->path : pair1->one->path;
		one.path = pair1->one->path;
		a.path = (char *)path1;
		b.path = (char *)path2;

		if (dir_in_way(o->repo->index, path, !o->call_depth,
			       S_ISGITLINK(pair1->two->mode)))
			df_conflict_remains = 1;
	}
	if (merge_mode_and_contents(o, &one, &a, &b, path,
				    o->branch1, o->branch2,
				    o->call_depth * 2, &mfi))
		return -1;

	/*
	 * We can skip updating the working tree file iff:
	 *   a) The merge is clean
	 *   b) The merge matches what was in HEAD (content, mode, pathname)
	 *   c) The target path is usable (i.e. not involved in D/F conflict)
	 */
	if (mfi.clean &&
	    was_tracked_and_matches(o, path, &mfi.oid, mfi.mode) &&
	    !df_conflict_remains) {
		int pos;
		struct cache_entry *ce;

		output(o, 3, _("Skipped %s (merged same as existing)"), path);
		if (add_cacheinfo(o, mfi.mode, &mfi.oid, path,
				  0, (!o->call_depth && !is_dirty), 0))
			return -1;
		/*
		 * However, add_cacheinfo() will delete the old cache entry
		 * and add a new one.  We need to copy over any skip_worktree
		 * flag to avoid making the file appear as if it were
		 * deleted by the user.
		 */
		pos = index_name_pos(&o->orig_index, path, strlen(path));
		ce = o->orig_index.cache[pos];
		if (ce_skip_worktree(ce)) {
			pos = index_name_pos(o->repo->index, path, strlen(path));
			ce = o->repo->index->cache[pos];
			ce->ce_flags |= CE_SKIP_WORKTREE;
		}
		return mfi.clean;
	}

	if (!mfi.clean) {
		if (S_ISGITLINK(mfi.mode))
			reason = _("submodule");
		output(o, 1, _("CONFLICT (%s): Merge conflict in %s"),
				reason, path);
		if (rename_conflict_info && !df_conflict_remains)
			if (update_stages(o, path, &one, &a, &b))
				return -1;
	}

	if (df_conflict_remains || is_dirty) {
		char *new_path;
		if (o->call_depth) {
			remove_file_from_index(o->repo->index, path);
		} else {
			if (!mfi.clean) {
				if (update_stages(o, path, &one, &a, &b))
					return -1;
			} else {
				int file_from_stage2 = was_tracked(o, path);
				struct diff_filespec merged;
				oidcpy(&merged.oid, &mfi.oid);
				merged.mode = mfi.mode;

				if (update_stages(o, path, NULL,
						  file_from_stage2 ? &merged : NULL,
						  file_from_stage2 ? NULL : &merged))
					return -1;
			}

		}
		new_path = unique_path(o, path, rename_conflict_info->branch1);
		if (is_dirty) {
			output(o, 1, _("Refusing to lose dirty file at %s"),
			       path);
		}
		output(o, 1, _("Adding as %s instead"), new_path);
		if (update_file(o, 0, &mfi.oid, mfi.mode, new_path)) {
			free(new_path);
			return -1;
		}
		free(new_path);
		mfi.clean = 0;
	} else if (update_file(o, mfi.clean, &mfi.oid, mfi.mode, path))
		return -1;
	return !is_dirty && mfi.clean;
}