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
typedef  int /*<<< orphan*/  uint64_t ;
struct strbuf {int dummy; } ;
struct child_process {int /*<<< orphan*/  argv; scalar_t__ git_cmd; int /*<<< orphan*/  dir; int /*<<< orphan*/  trace2_child_id; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  normal_io_write_fl (char const*,int,struct strbuf*) ; 
 int /*<<< orphan*/  sq_append_quote_argv_pretty (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sq_quote_buf_pretty (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void fn_child_start_fl(const char *file, int line,
			      uint64_t us_elapsed_absolute,
			      const struct child_process *cmd)
{
	struct strbuf buf_payload = STRBUF_INIT;

	strbuf_addf(&buf_payload, "child_start[%d]", cmd->trace2_child_id);

	if (cmd->dir) {
		strbuf_addstr(&buf_payload, " cd ");
		sq_quote_buf_pretty(&buf_payload, cmd->dir);
		strbuf_addstr(&buf_payload, ";");
	}

	/*
	 * TODO if (cmd->env) { Consider dumping changes to environment. }
	 * See trace_add_env() in run-command.c as used by original trace.c
	 */

	strbuf_addch(&buf_payload, ' ');
	if (cmd->git_cmd)
		strbuf_addstr(&buf_payload, "git ");
	sq_append_quote_argv_pretty(&buf_payload, cmd->argv);

	normal_io_write_fl(file, line, &buf_payload);
	strbuf_release(&buf_payload);
}