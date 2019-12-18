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
struct stash_info {int /*<<< orphan*/  w_tree; int /*<<< orphan*/  b_commit; int /*<<< orphan*/  i_tree; } ;
struct TYPE_3__ {int /*<<< orphan*/  pathspec; struct strbuf* format_callback_data; int /*<<< orphan*/  format_callback; int /*<<< orphan*/  output_format; } ;
struct rev_info {int /*<<< orphan*/  prune_data; int /*<<< orphan*/  pending; TYPE_1__ diffopt; } ;
struct pathspec {int dummy; } ;
struct index_state {int /*<<< orphan*/ * member_0; } ;
struct child_process {int git_cmd; int /*<<< orphan*/  env_array; int /*<<< orphan*/  args; } ;
struct TYPE_4__ {int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  DIFF_FORMAT_CALLBACK ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  UNLEAK (struct rev_info) ; 
 int /*<<< orphan*/  add_diff_to_buf ; 
 int /*<<< orphan*/  add_pending_object (struct rev_info*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_pathspec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_pathspec (int /*<<< orphan*/ *,struct pathspec const*) ; 
 int /*<<< orphan*/  discard_index (struct index_state*) ; 
 int /*<<< orphan*/  init_revisions (struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  object_array_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pipe_command (struct child_process*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ read_cache_preload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_path (int /*<<< orphan*/ *) ; 
 scalar_t__ reset_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ run_diff_index (struct rev_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_alternate_index_output (int /*<<< orphan*/ *) ; 
 TYPE_2__ stash_index_path ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 
 scalar_t__ write_index_as_tree (int /*<<< orphan*/ *,struct index_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stash_working_tree(struct stash_info *info, const struct pathspec *ps)
{
	int ret = 0;
	struct rev_info rev;
	struct child_process cp_upd_index = CHILD_PROCESS_INIT;
	struct strbuf diff_output = STRBUF_INIT;
	struct index_state istate = { NULL };

	init_revisions(&rev, NULL);
	copy_pathspec(&rev.prune_data, ps);

	set_alternate_index_output(stash_index_path.buf);
	if (reset_tree(&info->i_tree, 0, 0)) {
		ret = -1;
		goto done;
	}
	set_alternate_index_output(NULL);

	rev.diffopt.output_format = DIFF_FORMAT_CALLBACK;
	rev.diffopt.format_callback = add_diff_to_buf;
	rev.diffopt.format_callback_data = &diff_output;

	if (read_cache_preload(&rev.diffopt.pathspec) < 0) {
		ret = -1;
		goto done;
	}

	add_pending_object(&rev, parse_object(the_repository, &info->b_commit),
			   "");
	if (run_diff_index(&rev, 0)) {
		ret = -1;
		goto done;
	}

	cp_upd_index.git_cmd = 1;
	argv_array_pushl(&cp_upd_index.args, "update-index",
			 "--ignore-skip-worktree-entries",
			 "-z", "--add", "--remove", "--stdin", NULL);
	argv_array_pushf(&cp_upd_index.env_array, "GIT_INDEX_FILE=%s",
			 stash_index_path.buf);

	if (pipe_command(&cp_upd_index, diff_output.buf, diff_output.len,
			 NULL, 0, NULL, 0)) {
		ret = -1;
		goto done;
	}

	if (write_index_as_tree(&info->w_tree, &istate, stash_index_path.buf, 0,
				NULL)) {
		ret = -1;
		goto done;
	}

done:
	discard_index(&istate);
	UNLEAK(rev);
	object_array_clear(&rev.pending);
	clear_pathspec(&rev.prune_data);
	strbuf_release(&diff_output);
	remove_path(stash_index_path.buf);
	return ret;
}