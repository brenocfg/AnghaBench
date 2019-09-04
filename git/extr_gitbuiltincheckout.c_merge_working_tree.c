#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  topts ;
struct unpack_trees_options {int head_idx; int update; int merge; int quiet; TYPE_1__* dir; int /*<<< orphan*/  fn; int /*<<< orphan*/  verbose_update; int /*<<< orphan*/  initial_checkout; int /*<<< orphan*/ * dst_index; int /*<<< orphan*/ * src_index; } ;
struct tree_desc {int dummy; } ;
struct tree {int /*<<< orphan*/  size; int /*<<< orphan*/  buffer; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct merge_options {char* branch2; struct strbuf obuf; int /*<<< orphan*/  branch1; int /*<<< orphan*/  ancestor; scalar_t__ verbosity; } ;
struct lock_file {int dummy; } ;
struct checkout_opts {int /*<<< orphan*/  diff_options; int /*<<< orphan*/  quiet; scalar_t__ force; scalar_t__ merge; scalar_t__ overwrite_ignore; int /*<<< orphan*/  show_progress; } ;
struct branch_info {TYPE_5__* commit; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  oid; } ;
struct TYPE_9__ {TYPE_3__ object; } ;
struct TYPE_7__ {int /*<<< orphan*/ * empty_tree; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_LOCK ; 
 int /*<<< orphan*/  DIR_SHOW_IGNORED ; 
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 struct lock_file LOCK_INIT ; 
 int /*<<< orphan*/  REFRESH_QUIET ; 
 struct strbuf STRBUF_INIT ; 
 int WRITE_TREE_REPAIR ; 
 int WRITE_TREE_SILENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ active_cache_tree ; 
 int /*<<< orphan*/  add_files_to_cache (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cache_tree () ; 
 int /*<<< orphan*/  cache_tree_fully_valid (scalar_t__) ; 
 int /*<<< orphan*/  cache_tree_update (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clear_unpack_trees_porcelain (struct unpack_trees_options*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 struct tree* get_commit_tree (TYPE_5__*) ; 
 int /*<<< orphan*/  hold_locked_index (struct lock_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_merge_options (struct merge_options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_cache_unborn () ; 
 int /*<<< orphan*/  memset (struct unpack_trees_options*,int /*<<< orphan*/ ,int) ; 
 int merge_trees (struct merge_options*,struct tree*,struct tree*,struct tree*,struct tree**) ; 
 struct tree* parse_tree_indirect (int /*<<< orphan*/ *) ; 
 scalar_t__ read_cache_preload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refresh_cache (int /*<<< orphan*/ ) ; 
 scalar_t__ repo_index_has_changes (int /*<<< orphan*/ ,struct tree*,struct strbuf*) ; 
 int reset_tree (struct tree*,struct checkout_opts const*,int,int*) ; 
 int /*<<< orphan*/  resolve_undo_clear () ; 
 int /*<<< orphan*/  setup_standard_excludes (TYPE_1__*) ; 
 int /*<<< orphan*/  setup_unpack_trees_porcelain (struct unpack_trees_options*,char*) ; 
 int /*<<< orphan*/  show_local_changes (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 TYPE_2__* the_hash_algo ; 
 int /*<<< orphan*/  the_index ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  twoway_merge ; 
 scalar_t__ unmerged_cache () ; 
 int unpack_trees (int,struct tree_desc*,struct unpack_trees_options*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write_locked_index (int /*<<< orphan*/ *,struct lock_file*,int /*<<< orphan*/ ) ; 
 struct tree* write_tree_from_memory (struct merge_options*) ; 
 TYPE_1__* xcalloc (int,int) ; 

__attribute__((used)) static int merge_working_tree(const struct checkout_opts *opts,
			      struct branch_info *old_branch_info,
			      struct branch_info *new_branch_info,
			      int *writeout_error)
{
	int ret;
	struct lock_file lock_file = LOCK_INIT;

	hold_locked_index(&lock_file, LOCK_DIE_ON_ERROR);
	if (read_cache_preload(NULL) < 0)
		return error(_("index file corrupt"));

	resolve_undo_clear();
	if (opts->force) {
		ret = reset_tree(get_commit_tree(new_branch_info->commit),
				 opts, 1, writeout_error);
		if (ret)
			return ret;
	} else {
		struct tree_desc trees[2];
		struct tree *tree;
		struct unpack_trees_options topts;

		memset(&topts, 0, sizeof(topts));
		topts.head_idx = -1;
		topts.src_index = &the_index;
		topts.dst_index = &the_index;

		setup_unpack_trees_porcelain(&topts, "checkout");

		refresh_cache(REFRESH_QUIET);

		if (unmerged_cache()) {
			error(_("you need to resolve your current index first"));
			return 1;
		}

		/* 2-way merge to the new branch */
		topts.initial_checkout = is_cache_unborn();
		topts.update = 1;
		topts.merge = 1;
		topts.quiet = opts->merge && old_branch_info->commit;
		topts.verbose_update = opts->show_progress;
		topts.fn = twoway_merge;
		if (opts->overwrite_ignore) {
			topts.dir = xcalloc(1, sizeof(*topts.dir));
			topts.dir->flags |= DIR_SHOW_IGNORED;
			setup_standard_excludes(topts.dir);
		}
		tree = parse_tree_indirect(old_branch_info->commit ?
					   &old_branch_info->commit->object.oid :
					   the_hash_algo->empty_tree);
		init_tree_desc(&trees[0], tree->buffer, tree->size);
		tree = parse_tree_indirect(&new_branch_info->commit->object.oid);
		init_tree_desc(&trees[1], tree->buffer, tree->size);

		ret = unpack_trees(2, trees, &topts);
		clear_unpack_trees_porcelain(&topts);
		if (ret == -1) {
			/*
			 * Unpack couldn't do a trivial merge; either
			 * give up or do a real merge, depending on
			 * whether the merge flag was used.
			 */
			struct tree *result;
			struct tree *work;
			struct tree *old_tree;
			struct merge_options o;
			struct strbuf sb = STRBUF_INIT;

			if (!opts->merge)
				return 1;

			/*
			 * Without old_branch_info->commit, the below is the same as
			 * the two-tree unpack we already tried and failed.
			 */
			if (!old_branch_info->commit)
				return 1;
			old_tree = get_commit_tree(old_branch_info->commit);

			if (repo_index_has_changes(the_repository, old_tree, &sb))
				die(_("cannot continue with staged changes in "
				      "the following files:\n%s"), sb.buf);
			strbuf_release(&sb);

			if (repo_index_has_changes(the_repository,
						   get_commit_tree(old_branch_info->commit),
						   &sb))
				warning(_("staged changes in the following files may be lost: %s"),
					sb.buf);
			strbuf_release(&sb);

			/* Do more real merge */

			/*
			 * We update the index fully, then write the
			 * tree from the index, then merge the new
			 * branch with the current tree, with the old
			 * branch as the base. Then we reset the index
			 * (but not the working tree) to the new
			 * branch, leaving the working tree as the
			 * merged version, but skipping unmerged
			 * entries in the index.
			 */

			add_files_to_cache(NULL, NULL, 0);
			/*
			 * NEEDSWORK: carrying over local changes
			 * when branches have different end-of-line
			 * normalization (or clean+smudge rules) is
			 * a pain; plumb in an option to set
			 * o.renormalize?
			 */
			init_merge_options(&o, the_repository);
			o.verbosity = 0;
			work = write_tree_from_memory(&o);

			ret = reset_tree(get_commit_tree(new_branch_info->commit),
					 opts, 1,
					 writeout_error);
			if (ret)
				return ret;
			o.ancestor = old_branch_info->name;
			o.branch1 = new_branch_info->name;
			o.branch2 = "local";
			ret = merge_trees(&o,
					  get_commit_tree(new_branch_info->commit),
					  work,
					  old_tree,
					  &result);
			if (ret < 0)
				exit(128);
			ret = reset_tree(get_commit_tree(new_branch_info->commit),
					 opts, 0,
					 writeout_error);
			strbuf_release(&o.obuf);
			if (ret)
				return ret;
		}
	}

	if (!active_cache_tree)
		active_cache_tree = cache_tree();

	if (!cache_tree_fully_valid(active_cache_tree))
		cache_tree_update(&the_index, WRITE_TREE_SILENT | WRITE_TREE_REPAIR);

	if (write_locked_index(&the_index, &lock_file, COMMIT_LOCK))
		die(_("unable to write new index file"));

	if (!opts->force && !opts->quiet)
		show_local_changes(&new_branch_info->commit->object, &opts->diff_options);

	return 0;
}