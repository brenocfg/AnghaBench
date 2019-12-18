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
struct TYPE_3__ {int /*<<< orphan*/  nsec; int /*<<< orphan*/  sec; } ;
struct pattern_list {int initialized; int cache_nr; int updated_workdir; scalar_t__ cache_tree; struct cache_entry** cache; int /*<<< orphan*/  oid; TYPE_2__* split_index; int /*<<< orphan*/  version; TYPE_1__ timestamp; } ;
struct unpack_trees_options {int skip_sparse_checkout; unsigned int merge_size; char* prefix; scalar_t__ exiting_early; struct pattern_list* src_index; scalar_t__ show_all_errors; struct pattern_list result; struct pattern_list* dst_index; struct pattern_list* pl; scalar_t__ nontrivial_merge; scalar_t__ trivial_merges_only; scalar_t__ merge; int /*<<< orphan*/  pathspec; struct cache_entry* df_conflict_entry; int /*<<< orphan*/  update; } ;
struct tree_desc {int dummy; } ;
struct traverse_info {int /*<<< orphan*/  pathspec; scalar_t__ show_all_errors; struct unpack_trees_options* data; int /*<<< orphan*/  fn; } ;
struct cache_entry {int ce_flags; } ;
typedef  int /*<<< orphan*/  pl ;
struct TYPE_4__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int CE_ADDED ; 
 int CE_NEW_SKIP_WORKTREE ; 
 int CE_SKIP_WORKTREE ; 
 int /*<<< orphan*/  ERROR_WOULD_LOSE_UNTRACKED_OVERWRITTEN ; 
 unsigned int MAX_UNPACK_TREES ; 
 int WRITE_TREE_REPAIR ; 
 int WRITE_TREE_SILENT ; 
 scalar_t__ add_patterns_from_file_to_list (char*,char*,int /*<<< orphan*/ ,struct pattern_list*,int /*<<< orphan*/ *) ; 
 scalar_t__ apply_sparse_checkout (struct pattern_list*,struct cache_entry*,struct unpack_trees_options*) ; 
 int /*<<< orphan*/  cache_entry_size (int /*<<< orphan*/ ) ; 
 scalar_t__ cache_tree () ; 
 int /*<<< orphan*/  cache_tree_fully_valid (scalar_t__) ; 
 int /*<<< orphan*/  cache_tree_update (struct pattern_list*,int) ; 
 int /*<<< orphan*/  cache_tree_verify (int /*<<< orphan*/ ,struct pattern_list*) ; 
 scalar_t__ ce_in_traverse_path (struct cache_entry*,struct traverse_info*) ; 
 int /*<<< orphan*/  ce_skip_worktree (struct cache_entry*) ; 
 scalar_t__ check_updates (struct unpack_trees_options*) ; 
 int /*<<< orphan*/  clear_pattern_list (struct pattern_list*) ; 
 int /*<<< orphan*/  core_apply_sparse_checkout ; 
 int /*<<< orphan*/  die (char*,unsigned int) ; 
 int /*<<< orphan*/  discard_index (struct pattern_list*) ; 
 int /*<<< orphan*/  display_error_msgs (struct unpack_trees_options*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ git_env_bool (char*,int /*<<< orphan*/ ) ; 
 char* git_pathdup (char*) ; 
 TYPE_2__* init_split_index (struct pattern_list*) ; 
 int /*<<< orphan*/  mark_all_ce_unused (struct pattern_list*) ; 
 int /*<<< orphan*/  mark_new_skip_worktree (struct pattern_list*,struct pattern_list*,int,int) ; 
 int /*<<< orphan*/  memset (struct pattern_list*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  move_index_extensions (struct pattern_list*,struct pattern_list*) ; 
 struct cache_entry* next_cache_entry (struct unpack_trees_options*) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_traverse_info (struct traverse_info*,char const*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  trace_performance_enter () ; 
 int /*<<< orphan*/  trace_performance_leave (char*) ; 
 int traverse_trees (struct pattern_list*,unsigned int,struct tree_desc*,struct traverse_info*) ; 
 int /*<<< orphan*/  unpack_callback ; 
 int unpack_failed (struct unpack_trees_options*,char*) ; 
 scalar_t__ unpack_index_entry (struct cache_entry*,struct unpack_trees_options*) ; 
 scalar_t__ verify_absent (struct cache_entry*,int /*<<< orphan*/ ,struct unpack_trees_options*) ; 
 struct cache_entry* xcalloc (int,int /*<<< orphan*/ ) ; 

int unpack_trees(unsigned len, struct tree_desc *t, struct unpack_trees_options *o)
{
	int i, ret;
	static struct cache_entry *dfc;
	struct pattern_list pl;

	if (len > MAX_UNPACK_TREES)
		die("unpack_trees takes at most %d trees", MAX_UNPACK_TREES);

	trace_performance_enter();
	memset(&pl, 0, sizeof(pl));
	if (!core_apply_sparse_checkout || !o->update)
		o->skip_sparse_checkout = 1;
	if (!o->skip_sparse_checkout) {
		char *sparse = git_pathdup("info/sparse-checkout");
		if (add_patterns_from_file_to_list(sparse, "", 0, &pl, NULL) < 0)
			o->skip_sparse_checkout = 1;
		else
			o->pl = &pl;
		free(sparse);
	}

	memset(&o->result, 0, sizeof(o->result));
	o->result.initialized = 1;
	o->result.timestamp.sec = o->src_index->timestamp.sec;
	o->result.timestamp.nsec = o->src_index->timestamp.nsec;
	o->result.version = o->src_index->version;
	if (!o->src_index->split_index) {
		o->result.split_index = NULL;
	} else if (o->src_index == o->dst_index) {
		/*
		 * o->dst_index (and thus o->src_index) will be discarded
		 * and overwritten with o->result at the end of this function,
		 * so just use src_index's split_index to avoid having to
		 * create a new one.
		 */
		o->result.split_index = o->src_index->split_index;
		o->result.split_index->refcount++;
	} else {
		o->result.split_index = init_split_index(&o->result);
	}
	oidcpy(&o->result.oid, &o->src_index->oid);
	o->merge_size = len;
	mark_all_ce_unused(o->src_index);

	/*
	 * Sparse checkout loop #1: set NEW_SKIP_WORKTREE on existing entries
	 */
	if (!o->skip_sparse_checkout)
		mark_new_skip_worktree(o->pl, o->src_index, 0, CE_NEW_SKIP_WORKTREE);

	if (!dfc)
		dfc = xcalloc(1, cache_entry_size(0));
	o->df_conflict_entry = dfc;

	if (len) {
		const char *prefix = o->prefix ? o->prefix : "";
		struct traverse_info info;

		setup_traverse_info(&info, prefix);
		info.fn = unpack_callback;
		info.data = o;
		info.show_all_errors = o->show_all_errors;
		info.pathspec = o->pathspec;

		if (o->prefix) {
			/*
			 * Unpack existing index entries that sort before the
			 * prefix the tree is spliced into.  Note that o->merge
			 * is always true in this case.
			 */
			while (1) {
				struct cache_entry *ce = next_cache_entry(o);
				if (!ce)
					break;
				if (ce_in_traverse_path(ce, &info))
					break;
				if (unpack_index_entry(ce, o) < 0)
					goto return_failed;
			}
		}

		trace_performance_enter();
		ret = traverse_trees(o->src_index, len, t, &info);
		trace_performance_leave("traverse_trees");
		if (ret < 0)
			goto return_failed;
	}

	/* Any left-over entries in the index? */
	if (o->merge) {
		while (1) {
			struct cache_entry *ce = next_cache_entry(o);
			if (!ce)
				break;
			if (unpack_index_entry(ce, o) < 0)
				goto return_failed;
		}
	}
	mark_all_ce_unused(o->src_index);

	if (o->trivial_merges_only && o->nontrivial_merge) {
		ret = unpack_failed(o, "Merge requires file-level merging");
		goto done;
	}

	if (!o->skip_sparse_checkout) {
		int empty_worktree = 1;

		/*
		 * Sparse checkout loop #2: set NEW_SKIP_WORKTREE on entries not in loop #1
		 * If the will have NEW_SKIP_WORKTREE, also set CE_SKIP_WORKTREE
		 * so apply_sparse_checkout() won't attempt to remove it from worktree
		 */
		mark_new_skip_worktree(o->pl, &o->result, CE_ADDED, CE_SKIP_WORKTREE | CE_NEW_SKIP_WORKTREE);

		ret = 0;
		for (i = 0; i < o->result.cache_nr; i++) {
			struct cache_entry *ce = o->result.cache[i];

			/*
			 * Entries marked with CE_ADDED in merged_entry() do not have
			 * verify_absent() check (the check is effectively disabled
			 * because CE_NEW_SKIP_WORKTREE is set unconditionally).
			 *
			 * Do the real check now because we have had
			 * correct CE_NEW_SKIP_WORKTREE
			 */
			if (ce->ce_flags & CE_ADDED &&
			    verify_absent(ce, ERROR_WOULD_LOSE_UNTRACKED_OVERWRITTEN, o)) {
				if (!o->show_all_errors)
					goto return_failed;
				ret = -1;
			}

			if (apply_sparse_checkout(&o->result, ce, o)) {
				if (!o->show_all_errors)
					goto return_failed;
				ret = -1;
			}
			if (!ce_skip_worktree(ce))
				empty_worktree = 0;

		}
		if (ret < 0)
			goto return_failed;
		/*
		 * Sparse checkout is meant to narrow down checkout area
		 * but it does not make sense to narrow down to empty working
		 * tree. This is usually a mistake in sparse checkout rules.
		 * Do not allow users to do that.
		 */
		if (o->result.cache_nr && empty_worktree) {
			ret = unpack_failed(o, "Sparse checkout leaves no entry on working directory");
			goto done;
		}
	}

	ret = check_updates(o) ? (-2) : 0;
	if (o->dst_index) {
		move_index_extensions(&o->result, o->src_index);
		if (!ret) {
			if (git_env_bool("GIT_TEST_CHECK_CACHE_TREE", 0))
				cache_tree_verify(the_repository, &o->result);
			if (!o->result.cache_tree)
				o->result.cache_tree = cache_tree();
			if (!cache_tree_fully_valid(o->result.cache_tree))
				cache_tree_update(&o->result,
						  WRITE_TREE_SILENT |
						  WRITE_TREE_REPAIR);
		}

		o->result.updated_workdir = 1;
		discard_index(o->dst_index);
		*o->dst_index = o->result;
	} else {
		discard_index(&o->result);
	}
	o->src_index = NULL;

done:
	trace_performance_leave("unpack_trees");
	clear_pattern_list(&pl);
	return ret;

return_failed:
	if (o->show_all_errors)
		display_error_msgs(o);
	mark_all_ce_unused(o->src_index);
	ret = unpack_failed(o, NULL);
	if (o->exiting_early)
		ret = 0;
	goto done;
}