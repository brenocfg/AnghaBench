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
struct tree {int dummy; } ;
struct strbuf {int dummy; } ;
struct repository {int /*<<< orphan*/  index; } ;
struct replay_opts {char** xopts; int xopts_nr; int /*<<< orphan*/  default_msg_cleanup; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct merge_options {char const* ancestor; char* branch1; char const* branch2; int buffer_output; int show_rename_progress; TYPE_1__ obuf; } ;
struct lock_file {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int COMMIT_LOCK ; 
 struct lock_file LOCK_INIT ; 
 int /*<<< orphan*/  LOCK_REPORT_ON_ERROR ; 
 int SKIP_IF_UNCHANGED ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* action_name (struct replay_opts*) ; 
 int /*<<< orphan*/  append_conflicts_hint (int /*<<< orphan*/ ,struct strbuf*,int /*<<< orphan*/ ) ; 
 struct tree* empty_tree (struct repository*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tree* get_commit_tree (struct commit*) ; 
 int /*<<< orphan*/  init_merge_options (struct merge_options*,struct repository*) ; 
 scalar_t__ is_rebase_i (struct replay_opts*) ; 
 int merge_trees (struct merge_options*,struct tree*,struct tree*,struct tree*) ; 
 int /*<<< orphan*/  parse_merge_opt (struct merge_options*,char*) ; 
 struct tree* parse_tree_indirect (struct object_id*) ; 
 scalar_t__ repo_hold_locked_index (struct repository*,struct lock_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo_read_index (struct repository*) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strbuf_release (TYPE_1__*) ; 
 scalar_t__ write_locked_index (int /*<<< orphan*/ ,struct lock_file*,int) ; 

__attribute__((used)) static int do_recursive_merge(struct repository *r,
			      struct commit *base, struct commit *next,
			      const char *base_label, const char *next_label,
			      struct object_id *head, struct strbuf *msgbuf,
			      struct replay_opts *opts)
{
	struct merge_options o;
	struct tree *next_tree, *base_tree, *head_tree;
	int clean;
	char **xopt;
	struct lock_file index_lock = LOCK_INIT;

	if (repo_hold_locked_index(r, &index_lock, LOCK_REPORT_ON_ERROR) < 0)
		return -1;

	repo_read_index(r);

	init_merge_options(&o, r);
	o.ancestor = base ? base_label : "(empty tree)";
	o.branch1 = "HEAD";
	o.branch2 = next ? next_label : "(empty tree)";
	if (is_rebase_i(opts))
		o.buffer_output = 2;
	o.show_rename_progress = 1;

	head_tree = parse_tree_indirect(head);
	next_tree = next ? get_commit_tree(next) : empty_tree(r);
	base_tree = base ? get_commit_tree(base) : empty_tree(r);

	for (xopt = opts->xopts; xopt != opts->xopts + opts->xopts_nr; xopt++)
		parse_merge_opt(&o, *xopt);

	clean = merge_trees(&o,
			    head_tree,
			    next_tree, base_tree);
	if (is_rebase_i(opts) && clean <= 0)
		fputs(o.obuf.buf, stdout);
	strbuf_release(&o.obuf);
	if (clean < 0) {
		rollback_lock_file(&index_lock);
		return clean;
	}

	if (write_locked_index(r->index, &index_lock,
			       COMMIT_LOCK | SKIP_IF_UNCHANGED))
		/*
		 * TRANSLATORS: %s will be "revert", "cherry-pick" or
		 * "rebase -i".
		 */
		return error(_("%s: Unable to write new index file"),
			_(action_name(opts)));

	if (!clean)
		append_conflicts_hint(r->index, msgbuf,
				      opts->default_msg_cleanup);

	return !clean;
}