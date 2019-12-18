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
struct child_process {int /*<<< orphan*/  argv; scalar_t__ git_cmd; int /*<<< orphan*/  env; int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  sq_quote_argv_pretty (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sq_quote_buf_pretty (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  trace_add_env (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_default_key ; 
 int /*<<< orphan*/  trace_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_want (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void trace_run_command(const struct child_process *cp)
{
	struct strbuf buf = STRBUF_INIT;

	if (!trace_want(&trace_default_key))
		return;

	strbuf_addstr(&buf, "trace: run_command:");
	if (cp->dir) {
		strbuf_addstr(&buf, " cd ");
		sq_quote_buf_pretty(&buf, cp->dir);
		strbuf_addch(&buf, ';');
	}
	/*
	 * The caller is responsible for initializing cp->env from
	 * cp->env_array if needed. We only check one place.
	 */
	if (cp->env)
		trace_add_env(&buf, cp->env);
	if (cp->git_cmd)
		strbuf_addstr(&buf, " git");
	sq_quote_argv_pretty(&buf, cp->argv);

	trace_printf("%s", buf.buf);
	strbuf_release(&buf);
}