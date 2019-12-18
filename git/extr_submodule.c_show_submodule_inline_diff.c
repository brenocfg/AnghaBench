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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct TYPE_3__ {scalar_t__ reverse_diff; } ;
struct diff_options {int /*<<< orphan*/  b_prefix; int /*<<< orphan*/  a_prefix; TYPE_1__ flags; int /*<<< orphan*/  use_color; } ;
struct commit_list {int dummy; } ;
struct commit {int dummy; } ;
struct child_process {int git_cmd; char const* dir; int out; int no_stdin; int /*<<< orphan*/  env_array; int /*<<< orphan*/  args; } ;
struct TYPE_4__ {struct object_id* empty_tree; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 unsigned int DIRTY_SUBMODULE_MODIFIED ; 
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_commit_marks (struct commit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_emit_submodule_error (struct diff_options*,char*) ; 
 int /*<<< orphan*/  diff_emit_submodule_pipethrough (struct diff_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 int /*<<< orphan*/  free (struct repository*) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 scalar_t__ is_null_oid (struct object_id*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 struct repository* open_submodule (char const*) ; 
 int /*<<< orphan*/  prepare_submodule_repo_env (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo_clear (struct repository*) ; 
 int /*<<< orphan*/  show_submodule_header (struct diff_options*,char const*,struct object_id*,struct object_id*,unsigned int,struct repository*,struct commit**,struct commit**,struct commit_list**) ; 
 scalar_t__ start_command (struct child_process*) ; 
 scalar_t__ strbuf_getwholeline_fd (struct strbuf*,int,char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 TYPE_2__* the_hash_algo ; 
 scalar_t__ want_color (int /*<<< orphan*/ ) ; 

void show_submodule_inline_diff(struct diff_options *o, const char *path,
		struct object_id *one, struct object_id *two,
		unsigned dirty_submodule)
{
	const struct object_id *old_oid = the_hash_algo->empty_tree, *new_oid = the_hash_algo->empty_tree;
	struct commit *left = NULL, *right = NULL;
	struct commit_list *merge_bases = NULL;
	struct child_process cp = CHILD_PROCESS_INIT;
	struct strbuf sb = STRBUF_INIT;
	struct repository *sub;

	sub = open_submodule(path);
	show_submodule_header(o, path, one, two, dirty_submodule,
			      sub, &left, &right, &merge_bases);

	/* We need a valid left and right commit to display a difference */
	if (!(left || is_null_oid(one)) ||
	    !(right || is_null_oid(two)))
		goto done;

	if (left)
		old_oid = one;
	if (right)
		new_oid = two;

	cp.git_cmd = 1;
	cp.dir = path;
	cp.out = -1;
	cp.no_stdin = 1;

	/* TODO: other options may need to be passed here. */
	argv_array_pushl(&cp.args, "diff", "--submodule=diff", NULL);
	argv_array_pushf(&cp.args, "--color=%s", want_color(o->use_color) ?
			 "always" : "never");

	if (o->flags.reverse_diff) {
		argv_array_pushf(&cp.args, "--src-prefix=%s%s/",
				 o->b_prefix, path);
		argv_array_pushf(&cp.args, "--dst-prefix=%s%s/",
				 o->a_prefix, path);
	} else {
		argv_array_pushf(&cp.args, "--src-prefix=%s%s/",
				 o->a_prefix, path);
		argv_array_pushf(&cp.args, "--dst-prefix=%s%s/",
				 o->b_prefix, path);
	}
	argv_array_push(&cp.args, oid_to_hex(old_oid));
	/*
	 * If the submodule has modified content, we will diff against the
	 * work tree, under the assumption that the user has asked for the
	 * diff format and wishes to actually see all differences even if they
	 * haven't yet been committed to the submodule yet.
	 */
	if (!(dirty_submodule & DIRTY_SUBMODULE_MODIFIED))
		argv_array_push(&cp.args, oid_to_hex(new_oid));

	prepare_submodule_repo_env(&cp.env_array);
	if (start_command(&cp))
		diff_emit_submodule_error(o, "(diff failed)\n");

	while (strbuf_getwholeline_fd(&sb, cp.out, '\n') != EOF)
		diff_emit_submodule_pipethrough(o, sb.buf, sb.len);

	if (finish_command(&cp))
		diff_emit_submodule_error(o, "(diff failed)\n");

done:
	strbuf_release(&sb);
	if (merge_bases)
		free_commit_list(merge_bases);
	if (left)
		clear_commit_marks(left, ~0);
	if (right)
		clear_commit_marks(right, ~0);
	if (sub) {
		repo_clear(sub);
		free(sub);
	}
}