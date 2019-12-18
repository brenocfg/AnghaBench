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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct commit_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 scalar_t__ COMMIT_MSG_CLEANUP_SCISSORS ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/ * _ (char*) ; 
 int /*<<< orphan*/  abort_commit (struct commit_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  append_signoff (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_message (struct strbuf*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ cleanup_mode ; 
 int /*<<< orphan*/  comment_line_char ; 
 int /*<<< orphan*/  discard_cache () ; 
 scalar_t__ find_hook (char*) ; 
 char* get_index_file () ; 
 int /*<<< orphan*/  git_path_merge_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignore_non_trailer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ launch_editor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* merge_editor_comment ; 
 struct strbuf merge_msg ; 
 char* no_scissors_editor_comment ; 
 int /*<<< orphan*/  no_verify ; 
 scalar_t__ option_edit ; 
 int /*<<< orphan*/  read_cache_from (char const*) ; 
 int /*<<< orphan*/  read_merge_msg (struct strbuf*) ; 
 scalar_t__ run_commit_hook (int,char const*,char*,int /*<<< orphan*/ ,...) ; 
 char* scissors_editor_comment ; 
 scalar_t__ signoff ; 
 scalar_t__ squash ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_commented_addf (struct strbuf*,char*,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  write_file_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_merge_heads (struct commit_list*) ; 
 int /*<<< orphan*/  wt_status_append_cut_line (struct strbuf*) ; 

__attribute__((used)) static void prepare_to_commit(struct commit_list *remoteheads)
{
	struct strbuf msg = STRBUF_INIT;
	const char *index_file = get_index_file();

	if (!no_verify && run_commit_hook(0 < option_edit, index_file, "pre-merge-commit", NULL))
		abort_commit(remoteheads, NULL);
	/*
	 * Re-read the index as pre-merge-commit hook could have updated it,
	 * and write it out as a tree.  We must do this before we invoke
	 * the editor and after we invoke run_status above.
	 */
	if (find_hook("pre-merge-commit"))
		discard_cache();
	read_cache_from(index_file);
	strbuf_addbuf(&msg, &merge_msg);
	if (squash)
		BUG("the control must not reach here under --squash");
	if (0 < option_edit) {
		strbuf_addch(&msg, '\n');
		if (cleanup_mode == COMMIT_MSG_CLEANUP_SCISSORS) {
			wt_status_append_cut_line(&msg);
			strbuf_commented_addf(&msg, "\n");
		}
		strbuf_commented_addf(&msg, _(merge_editor_comment));
		strbuf_commented_addf(&msg, _(cleanup_mode == COMMIT_MSG_CLEANUP_SCISSORS ?
			scissors_editor_comment :
			no_scissors_editor_comment), comment_line_char);
	}
	if (signoff)
		append_signoff(&msg, ignore_non_trailer(msg.buf, msg.len), 0);
	write_merge_heads(remoteheads);
	write_file_buf(git_path_merge_msg(the_repository), msg.buf, msg.len);
	if (run_commit_hook(0 < option_edit, get_index_file(), "prepare-commit-msg",
			    git_path_merge_msg(the_repository), "merge", NULL))
		abort_commit(remoteheads, NULL);
	if (0 < option_edit) {
		if (launch_editor(git_path_merge_msg(the_repository), NULL, NULL))
			abort_commit(remoteheads, NULL);
	}

	if (!no_verify && run_commit_hook(0 < option_edit, get_index_file(),
					  "commit-msg",
					  git_path_merge_msg(the_repository), NULL))
		abort_commit(remoteheads, NULL);

	read_merge_msg(&msg);
	cleanup_message(&msg, cleanup_mode, 0);
	if (!msg.len)
		abort_commit(remoteheads, _("Empty commit message."));
	strbuf_release(&merge_msg);
	strbuf_addbuf(&merge_msg, &msg);
	strbuf_release(&msg);
}