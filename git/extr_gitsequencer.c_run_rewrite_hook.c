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
struct object_id {int dummy; } ;
struct child_process {char const** argv; int in; int stdout_to_stderr; char* trace2_hook_name; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  close (int) ; 
 char* find_hook (char*) ; 
 int finish_command (struct child_process*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  sigchain_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigchain_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int start_command (struct child_process*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  write_in_full (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run_rewrite_hook(const struct object_id *oldoid,
			    const struct object_id *newoid)
{
	struct child_process proc = CHILD_PROCESS_INIT;
	const char *argv[3];
	int code;
	struct strbuf sb = STRBUF_INIT;

	argv[0] = find_hook("post-rewrite");
	if (!argv[0])
		return 0;

	argv[1] = "amend";
	argv[2] = NULL;

	proc.argv = argv;
	proc.in = -1;
	proc.stdout_to_stderr = 1;
	proc.trace2_hook_name = "post-rewrite";

	code = start_command(&proc);
	if (code)
		return code;
	strbuf_addf(&sb, "%s %s\n", oid_to_hex(oldoid), oid_to_hex(newoid));
	sigchain_push(SIGPIPE, SIG_IGN);
	write_in_full(proc.in, sb.buf, sb.len);
	close(proc.in);
	strbuf_release(&sb);
	sigchain_pop(SIGPIPE);
	return finish_command(&proc);
}