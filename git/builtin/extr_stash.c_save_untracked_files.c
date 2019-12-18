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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct stash_info {int /*<<< orphan*/  u_commit; int /*<<< orphan*/  u_tree; } ;
struct index_state {int /*<<< orphan*/ * member_0; } ;
struct child_process {int git_cmd; int /*<<< orphan*/  env_array; int /*<<< orphan*/  args; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ commit_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  discard_index (struct index_state*) ; 
 scalar_t__ pipe_command (struct child_process*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_path (int /*<<< orphan*/ ) ; 
 TYPE_1__ stash_index_path ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ write_index_as_tree (int /*<<< orphan*/ *,struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int save_untracked_files(struct stash_info *info, struct strbuf *msg,
				struct strbuf files)
{
	int ret = 0;
	struct strbuf untracked_msg = STRBUF_INIT;
	struct child_process cp_upd_index = CHILD_PROCESS_INIT;
	struct index_state istate = { NULL };

	cp_upd_index.git_cmd = 1;
	argv_array_pushl(&cp_upd_index.args, "update-index", "-z", "--add",
			 "--remove", "--stdin", NULL);
	argv_array_pushf(&cp_upd_index.env_array, "GIT_INDEX_FILE=%s",
			 stash_index_path.buf);

	strbuf_addf(&untracked_msg, "untracked files on %s\n", msg->buf);
	if (pipe_command(&cp_upd_index, files.buf, files.len, NULL, 0,
			 NULL, 0)) {
		ret = -1;
		goto done;
	}

	if (write_index_as_tree(&info->u_tree, &istate, stash_index_path.buf, 0,
				NULL)) {
		ret = -1;
		goto done;
	}

	if (commit_tree(untracked_msg.buf, untracked_msg.len,
			&info->u_tree, NULL, &info->u_commit, NULL, NULL)) {
		ret = -1;
		goto done;
	}

done:
	discard_index(&istate);
	strbuf_release(&untracked_msg);
	remove_path(stash_index_path.buf);
	return ret;
}