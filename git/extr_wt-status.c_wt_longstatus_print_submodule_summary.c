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
struct wt_status {int /*<<< orphan*/  fp; scalar_t__ display_comment_prefix; scalar_t__ amend; int /*<<< orphan*/  submodule_summary; int /*<<< orphan*/  index_file; } ;
struct strbuf {int /*<<< orphan*/  buf; scalar_t__ len; } ;
struct child_process {int git_cmd; int no_stdin; int /*<<< orphan*/  args; int /*<<< orphan*/  env_array; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capture_command (struct child_process*,struct strbuf*,int) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strbuf_add_commented_lines (struct strbuf*,char*,size_t) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 char* strbuf_detach (struct strbuf*,size_t*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void wt_longstatus_print_submodule_summary(struct wt_status *s, int uncommitted)
{
	struct child_process sm_summary = CHILD_PROCESS_INIT;
	struct strbuf cmd_stdout = STRBUF_INIT;
	struct strbuf summary = STRBUF_INIT;
	char *summary_content;

	argv_array_pushf(&sm_summary.env_array, "GIT_INDEX_FILE=%s",
			 s->index_file);

	argv_array_push(&sm_summary.args, "submodule");
	argv_array_push(&sm_summary.args, "summary");
	argv_array_push(&sm_summary.args, uncommitted ? "--files" : "--cached");
	argv_array_push(&sm_summary.args, "--for-status");
	argv_array_push(&sm_summary.args, "--summary-limit");
	argv_array_pushf(&sm_summary.args, "%d", s->submodule_summary);
	if (!uncommitted)
		argv_array_push(&sm_summary.args, s->amend ? "HEAD^" : "HEAD");

	sm_summary.git_cmd = 1;
	sm_summary.no_stdin = 1;

	capture_command(&sm_summary, &cmd_stdout, 1024);

	/* prepend header, only if there's an actual output */
	if (cmd_stdout.len) {
		if (uncommitted)
			strbuf_addstr(&summary, _("Submodules changed but not updated:"));
		else
			strbuf_addstr(&summary, _("Submodule changes to be committed:"));
		strbuf_addstr(&summary, "\n\n");
	}
	strbuf_addbuf(&summary, &cmd_stdout);
	strbuf_release(&cmd_stdout);

	if (s->display_comment_prefix) {
		size_t len;
		summary_content = strbuf_detach(&summary, &len);
		strbuf_add_commented_lines(&summary, summary_content, len);
		free(summary_content);
	}

	fputs(summary.buf, s->fp);
	strbuf_release(&summary);
}