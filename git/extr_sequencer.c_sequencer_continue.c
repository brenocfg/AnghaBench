#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct todo_list {int /*<<< orphan*/  current; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct repository {int dummy; } ;
struct replay_opts {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 struct todo_list TODO_LIST_INIT ; 
 scalar_t__ commit_staged_changes (struct repository*,struct replay_opts*,struct todo_list*) ; 
 int continue_single_pick (struct repository*) ; 
 int error_dirty_index (struct repository*,struct replay_opts*) ; 
 scalar_t__ file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_oid_committish (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  get_todo_path (struct replay_opts*) ; 
 int /*<<< orphan*/  git_path_cherry_pick_head (struct repository*) ; 
 int /*<<< orphan*/  git_path_revert_head (struct repository*) ; 
 scalar_t__ index_differs_from (struct repository*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_rebase_i (struct replay_opts*) ; 
 int /*<<< orphan*/  peek_command (struct todo_list*,int /*<<< orphan*/ ) ; 
 int pick_commits (struct repository*,struct todo_list*,struct replay_opts*) ; 
 scalar_t__ read_and_refresh_cache (struct repository*,struct replay_opts*) ; 
 scalar_t__ read_oneliner (struct strbuf*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ read_populate_opts (struct replay_opts*) ; 
 int read_populate_todo (struct repository*,struct todo_list*,struct replay_opts*) ; 
 int /*<<< orphan*/  rebase_path_stopped_sha () ; 
 int /*<<< orphan*/  record_in_rewritten (struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  todo_list_release (struct todo_list*) ; 

int sequencer_continue(struct repository *r, struct replay_opts *opts)
{
	struct todo_list todo_list = TODO_LIST_INIT;
	int res;

	if (read_and_refresh_cache(r, opts))
		return -1;

	if (read_populate_opts(opts))
		return -1;
	if (is_rebase_i(opts)) {
		if ((res = read_populate_todo(r, &todo_list, opts)))
			goto release_todo_list;
		if (commit_staged_changes(r, opts, &todo_list))
			return -1;
	} else if (!file_exists(get_todo_path(opts)))
		return continue_single_pick(r);
	else if ((res = read_populate_todo(r, &todo_list, opts)))
		goto release_todo_list;

	if (!is_rebase_i(opts)) {
		/* Verify that the conflict has been resolved */
		if (file_exists(git_path_cherry_pick_head(r)) ||
		    file_exists(git_path_revert_head(r))) {
			res = continue_single_pick(r);
			if (res)
				goto release_todo_list;
		}
		if (index_differs_from(r, "HEAD", NULL, 0)) {
			res = error_dirty_index(r, opts);
			goto release_todo_list;
		}
		todo_list.current++;
	} else if (file_exists(rebase_path_stopped_sha())) {
		struct strbuf buf = STRBUF_INIT;
		struct object_id oid;

		if (read_oneliner(&buf, rebase_path_stopped_sha(), 1) &&
		    !get_oid_committish(buf.buf, &oid))
			record_in_rewritten(&oid, peek_command(&todo_list, 0));
		strbuf_release(&buf);
	}

	res = pick_commits(r, &todo_list, opts);
release_todo_list:
	todo_list_release(&todo_list);
	return res;
}