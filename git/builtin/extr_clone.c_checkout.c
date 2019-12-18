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
struct unpack_trees_options {int update; int merge; int clone; int verbose_update; int /*<<< orphan*/ * dst_index; int /*<<< orphan*/ * src_index; int /*<<< orphan*/  fn; } ;
struct tree_desc {int dummy; } ;
struct tree {int /*<<< orphan*/  size; int /*<<< orphan*/  buffer; } ;
struct object_id {int dummy; } ;
struct lock_file {int dummy; } ;
struct argv_array {int /*<<< orphan*/  argv; } ;
struct TYPE_2__ {scalar_t__ nr; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  COMMIT_LOCK ; 
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 struct lock_file LOCK_INIT ; 
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ advice_detached_head ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char*) ; 
 int /*<<< orphan*/  argv_array_pushf (struct argv_array*,char*,int) ; 
 int /*<<< orphan*/  argv_array_pushl (struct argv_array*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  detach_advice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hold_locked_index (struct lock_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int max_jobs ; 
 int /*<<< orphan*/  memset (struct unpack_trees_options*,int /*<<< orphan*/ ,int) ; 
 struct object_id null_oid ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  oneway_merge ; 
 scalar_t__ option_no_checkout ; 
 TYPE_1__ option_recurse_submodules ; 
 scalar_t__ option_remote_submodules ; 
 int option_shallow_submodules ; 
 scalar_t__ option_verbosity ; 
 int /*<<< orphan*/  parse_tree (struct tree*) ; 
 struct tree* parse_tree_indirect (struct object_id*) ; 
 char* resolve_refdup (char*,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 int run_command_v_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int run_hook_le (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_work_tree () ; 
 int /*<<< orphan*/  starts_with (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  the_index ; 
 scalar_t__ unpack_trees (int,struct tree_desc*,struct unpack_trees_options*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ) ; 
 scalar_t__ write_locked_index (int /*<<< orphan*/ *,struct lock_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int checkout(int submodule_progress)
{
	struct object_id oid;
	char *head;
	struct lock_file lock_file = LOCK_INIT;
	struct unpack_trees_options opts;
	struct tree *tree;
	struct tree_desc t;
	int err = 0;

	if (option_no_checkout)
		return 0;

	head = resolve_refdup("HEAD", RESOLVE_REF_READING, &oid, NULL);
	if (!head) {
		warning(_("remote HEAD refers to nonexistent ref, "
			  "unable to checkout.\n"));
		return 0;
	}
	if (!strcmp(head, "HEAD")) {
		if (advice_detached_head)
			detach_advice(oid_to_hex(&oid));
	} else {
		if (!starts_with(head, "refs/heads/"))
			die(_("HEAD not found below refs/heads!"));
	}
	free(head);

	/* We need to be in the new work tree for the checkout */
	setup_work_tree();

	hold_locked_index(&lock_file, LOCK_DIE_ON_ERROR);

	memset(&opts, 0, sizeof opts);
	opts.update = 1;
	opts.merge = 1;
	opts.clone = 1;
	opts.fn = oneway_merge;
	opts.verbose_update = (option_verbosity >= 0);
	opts.src_index = &the_index;
	opts.dst_index = &the_index;

	tree = parse_tree_indirect(&oid);
	parse_tree(tree);
	init_tree_desc(&t, tree->buffer, tree->size);
	if (unpack_trees(1, &t, &opts) < 0)
		die(_("unable to checkout working tree"));

	if (write_locked_index(&the_index, &lock_file, COMMIT_LOCK))
		die(_("unable to write new index file"));

	err |= run_hook_le(NULL, "post-checkout", oid_to_hex(&null_oid),
			   oid_to_hex(&oid), "1", NULL);

	if (!err && (option_recurse_submodules.nr > 0)) {
		struct argv_array args = ARGV_ARRAY_INIT;
		argv_array_pushl(&args, "submodule", "update", "--init", "--recursive", NULL);

		if (option_shallow_submodules == 1)
			argv_array_push(&args, "--depth=1");

		if (max_jobs != -1)
			argv_array_pushf(&args, "--jobs=%d", max_jobs);

		if (submodule_progress)
			argv_array_push(&args, "--progress");

		if (option_verbosity < 0)
			argv_array_push(&args, "--quiet");

		if (option_remote_submodules) {
			argv_array_push(&args, "--remote");
			argv_array_push(&args, "--no-fetch");
		}

		err = run_command_v_opt(args.argv, RUN_GIT_CMD);
		argv_array_clear(&args);
	}

	return err;
}