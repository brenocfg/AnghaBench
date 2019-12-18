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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct child_process {int git_cmd; int /*<<< orphan*/  args; } ;
struct am_state {int cur; int /*<<< orphan*/  last; int /*<<< orphan*/  dir; int /*<<< orphan*/  prec; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_array_pushv (int /*<<< orphan*/ *,char const**) ; 
 int capture_command (struct child_process*,struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int split_mail_mbox(struct am_state *state, const char **paths,
				int keep_cr, int mboxrd)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	struct strbuf last = STRBUF_INIT;
	int ret;

	cp.git_cmd = 1;
	argv_array_push(&cp.args, "mailsplit");
	argv_array_pushf(&cp.args, "-d%d", state->prec);
	argv_array_pushf(&cp.args, "-o%s", state->dir);
	argv_array_push(&cp.args, "-b");
	if (keep_cr)
		argv_array_push(&cp.args, "--keep-cr");
	if (mboxrd)
		argv_array_push(&cp.args, "--mboxrd");
	argv_array_push(&cp.args, "--");
	argv_array_pushv(&cp.args, paths);

	ret = capture_command(&cp, &last, 8);
	if (ret)
		goto exit;

	state->cur = 1;
	state->last = strtol(last.buf, NULL, 10);

exit:
	strbuf_release(&last);
	return ret ? -1 : 0;
}