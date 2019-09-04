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
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/ * _ (char*) ; 
 int /*<<< orphan*/  abort_commit (struct commit_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  append_signoff (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comment_line_char ; 
 int /*<<< orphan*/  get_index_file () ; 
 int /*<<< orphan*/  git_path_merge_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignore_non_trailer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ launch_editor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* merge_editor_comment ; 
 struct strbuf merge_msg ; 
 scalar_t__ option_edit ; 
 int /*<<< orphan*/  read_merge_msg (struct strbuf*) ; 
 scalar_t__ run_commit_hook (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ signoff ; 
 scalar_t__ squash ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_commented_addf (struct strbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_stripspace (struct strbuf*,int) ; 
 int /*<<< orphan*/  the_repository ; 
 scalar_t__ verify_msg ; 
 int /*<<< orphan*/  write_file_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_merge_heads (struct commit_list*) ; 

__attribute__((used)) static void prepare_to_commit(struct commit_list *remoteheads)
{
	struct strbuf msg = STRBUF_INIT;
	strbuf_addbuf(&msg, &merge_msg);
	strbuf_addch(&msg, '\n');
	if (squash)
		BUG("the control must not reach here under --squash");
	if (0 < option_edit)
		strbuf_commented_addf(&msg, _(merge_editor_comment), comment_line_char);
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

	if (verify_msg && run_commit_hook(0 < option_edit, get_index_file(),
					  "commit-msg",
					  git_path_merge_msg(the_repository), NULL))
		abort_commit(remoteheads, NULL);

	read_merge_msg(&msg);
	strbuf_stripspace(&msg, 0 < option_edit);
	if (!msg.len)
		abort_commit(remoteheads, _("Empty commit message."));
	strbuf_release(&merge_msg);
	strbuf_addbuf(&merge_msg, &msg);
	strbuf_release(&msg);
}