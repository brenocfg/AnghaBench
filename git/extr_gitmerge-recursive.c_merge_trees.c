#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
struct tree {TYPE_1__ object; } ;
struct string_list {int nr; TYPE_2__* items; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct stage_data {int /*<<< orphan*/  processed; } ;
struct rename_info {int dummy; } ;
struct merge_options {scalar_t__ call_depth; int /*<<< orphan*/  current_file_dir_set; TYPE_3__* repo; scalar_t__ subtree_shift; } ;
struct index_state {int dummy; } ;
struct TYPE_7__ {struct index_state* index; } ;
struct TYPE_6__ {char* string; struct stage_data* util; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,char*) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int detect_and_process_renames (struct merge_options*,struct tree*,struct tree*,struct tree*,struct string_list*,struct rename_info*) ; 
 int /*<<< orphan*/  err (struct merge_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  final_cleanup_renames (struct rename_info*) ; 
 int /*<<< orphan*/  free (struct string_list*) ; 
 int /*<<< orphan*/  get_files_dirs (struct merge_options*,struct tree*) ; 
 struct string_list* get_unmerged (struct index_state*) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hashmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ oid_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output (struct merge_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_hashmap_cmp ; 
 int process_entry (struct merge_options*,char const*,struct stage_data*) ; 
 int /*<<< orphan*/  record_df_conflict_files (struct merge_options*,struct string_list*) ; 
 scalar_t__ repo_index_has_changes (TYPE_3__*,struct tree*,struct strbuf*) ; 
 struct tree* shift_tree_object (TYPE_3__*,struct tree*,struct tree*,scalar_t__) ; 
 scalar_t__ show (struct merge_options*,int) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int) ; 
 scalar_t__ unmerged_index (struct index_state*) ; 
 int /*<<< orphan*/  unpack_trees_finish (struct merge_options*) ; 
 int unpack_trees_start (struct merge_options*,struct tree*,struct tree*,struct tree*) ; 
 struct tree* write_tree_from_memory (struct merge_options*) ; 

int merge_trees(struct merge_options *o,
		struct tree *head,
		struct tree *merge,
		struct tree *common,
		struct tree **result)
{
	struct index_state *istate = o->repo->index;
	int code, clean;
	struct strbuf sb = STRBUF_INIT;

	if (!o->call_depth && repo_index_has_changes(o->repo, head, &sb)) {
		err(o, _("Your local changes to the following files would be overwritten by merge:\n  %s"),
		    sb.buf);
		return -1;
	}

	if (o->subtree_shift) {
		merge = shift_tree_object(o->repo, head, merge, o->subtree_shift);
		common = shift_tree_object(o->repo, head, common, o->subtree_shift);
	}

	if (oid_eq(&common->object.oid, &merge->object.oid)) {
		output(o, 0, _("Already up to date!"));
		*result = head;
		return 1;
	}

	code = unpack_trees_start(o, common, head, merge);

	if (code != 0) {
		if (show(o, 4) || o->call_depth)
			err(o, _("merging of trees %s and %s failed"),
			    oid_to_hex(&head->object.oid),
			    oid_to_hex(&merge->object.oid));
		unpack_trees_finish(o);
		return -1;
	}

	if (unmerged_index(istate)) {
		struct string_list *entries;
		struct rename_info re_info;
		int i;
		/*
		 * Only need the hashmap while processing entries, so
		 * initialize it here and free it when we are done running
		 * through the entries. Keeping it in the merge_options as
		 * opposed to decaring a local hashmap is for convenience
		 * so that we don't have to pass it to around.
		 */
		hashmap_init(&o->current_file_dir_set, path_hashmap_cmp, NULL, 512);
		get_files_dirs(o, head);
		get_files_dirs(o, merge);

		entries = get_unmerged(o->repo->index);
		clean = detect_and_process_renames(o, common, head, merge,
						   entries, &re_info);
		record_df_conflict_files(o, entries);
		if (clean < 0)
			goto cleanup;
		for (i = entries->nr-1; 0 <= i; i--) {
			const char *path = entries->items[i].string;
			struct stage_data *e = entries->items[i].util;
			if (!e->processed) {
				int ret = process_entry(o, path, e);
				if (!ret)
					clean = 0;
				else if (ret < 0) {
					clean = ret;
					goto cleanup;
				}
			}
		}
		for (i = 0; i < entries->nr; i++) {
			struct stage_data *e = entries->items[i].util;
			if (!e->processed)
				BUG("unprocessed path??? %s",
				    entries->items[i].string);
		}

	cleanup:
		final_cleanup_renames(&re_info);

		string_list_clear(entries, 1);
		free(entries);

		hashmap_free(&o->current_file_dir_set, 1);

		if (clean < 0) {
			unpack_trees_finish(o);
			return clean;
		}
	}
	else
		clean = 1;

	unpack_trees_finish(o);

	if (o->call_depth && !(*result = write_tree_from_memory(o)))
		return -1;

	return clean;
}