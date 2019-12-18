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
struct child_process {int no_stdin; int no_stdout; int no_stderr; int /*<<< orphan*/  args; int /*<<< orphan*/  env_array; scalar_t__ use_shell; } ;
typedef  enum ssh_variant { ____Placeholder_ssh_variant } ssh_variant ;
typedef  enum protocol_version { ____Placeholder_protocol_version } protocol_version ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int VARIANT_AUTO ; 
 int VARIANT_SIMPLE ; 
 int VARIANT_SSH ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char const*) ; 
 int determine_ssh_variant (char const*,int) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 char* get_ssh_command () ; 
 char* getenv (char*) ; 
 scalar_t__ looks_like_command_line_option (char const*) ; 
 int /*<<< orphan*/  push_ssh_options (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char const*,int,int) ; 
 scalar_t__ run_command (struct child_process*) ; 

__attribute__((used)) static void fill_ssh_args(struct child_process *conn, const char *ssh_host,
			  const char *port, enum protocol_version version,
			  int flags)
{
	const char *ssh;
	enum ssh_variant variant;

	if (looks_like_command_line_option(ssh_host))
		die(_("strange hostname '%s' blocked"), ssh_host);

	ssh = get_ssh_command();
	if (ssh) {
		variant = determine_ssh_variant(ssh, 1);
	} else {
		/*
		 * GIT_SSH is the no-shell version of
		 * GIT_SSH_COMMAND (and must remain so for
		 * historical compatibility).
		 */
		conn->use_shell = 0;

		ssh = getenv("GIT_SSH");
		if (!ssh)
			ssh = "ssh";
		variant = determine_ssh_variant(ssh, 0);
	}

	if (variant == VARIANT_AUTO) {
		struct child_process detect = CHILD_PROCESS_INIT;

		detect.use_shell = conn->use_shell;
		detect.no_stdin = detect.no_stdout = detect.no_stderr = 1;

		argv_array_push(&detect.args, ssh);
		argv_array_push(&detect.args, "-G");
		push_ssh_options(&detect.args, &detect.env_array,
				 VARIANT_SSH, port, version, flags);
		argv_array_push(&detect.args, ssh_host);

		variant = run_command(&detect) ? VARIANT_SIMPLE : VARIANT_SSH;
	}

	argv_array_push(&conn->args, ssh);
	push_ssh_options(&conn->args, &conn->env_array, variant, port, version, flags);
	argv_array_push(&conn->args, ssh_host);
}