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
struct child_process {int stdout_to_stderr; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pipe_command (struct child_process*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int run_command_silent_on_success(struct child_process *cmd)
{
	struct strbuf buf = STRBUF_INIT;
	int rc;

	cmd->stdout_to_stderr = 1;
	rc = pipe_command(cmd,
			  NULL, 0,
			  NULL, 0,
			  &buf, 0);

	if (rc)
		fputs(buf.buf, stderr);
	strbuf_release(&buf);
	return rc;
}