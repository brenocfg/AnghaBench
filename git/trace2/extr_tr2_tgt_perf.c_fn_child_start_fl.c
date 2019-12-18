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
struct child_process {char const* trace2_hook_name; char* trace2_child_class; scalar_t__* argv; scalar_t__ git_cmd; int /*<<< orphan*/  dir; int /*<<< orphan*/  trace2_child_id; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  perf_io_write_fl (char const*,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  sq_append_quote_argv_pretty (struct strbuf*,scalar_t__*) ; 
 int /*<<< orphan*/  sq_quote_buf_pretty (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void fn_child_start_fl(const char *file, int line,
			      uint64_t us_elapsed_absolute,
			      const struct child_process *cmd)
{
	const char *event_name = "child_start";
	struct strbuf buf_payload = STRBUF_INIT;

	if (cmd->trace2_hook_name) {
		strbuf_addf(&buf_payload, "[ch%d] class:hook hook:%s",
			    cmd->trace2_child_id, cmd->trace2_hook_name);
	} else {
		const char *child_class =
			cmd->trace2_child_class ? cmd->trace2_child_class : "?";
		strbuf_addf(&buf_payload, "[ch%d] class:%s",
			    cmd->trace2_child_id, child_class);
	}

	if (cmd->dir) {
		strbuf_addstr(&buf_payload, " cd:");
		sq_quote_buf_pretty(&buf_payload, cmd->dir);
	}

	strbuf_addstr(&buf_payload, " argv:[");
	if (cmd->git_cmd) {
		strbuf_addstr(&buf_payload, "git");
		if (cmd->argv[0])
			strbuf_addch(&buf_payload, ' ');
	}
	sq_append_quote_argv_pretty(&buf_payload, cmd->argv);
	strbuf_addch(&buf_payload, ']');

	perf_io_write_fl(file, line, event_name, NULL, &us_elapsed_absolute,
			 NULL, NULL, &buf_payload);
	strbuf_release(&buf_payload);
}