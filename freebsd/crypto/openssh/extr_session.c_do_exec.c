#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
typedef  int /*<<< orphan*/  session_type ;
struct TYPE_11__ {char* force_command; } ;
struct TYPE_10__ {char* adm_forced_command; } ;
struct TYPE_9__ {char* subsys; int ttyfd; char* tty; TYPE_1__* pw; int /*<<< orphan*/  self; scalar_t__ is_subsystem; } ;
struct TYPE_8__ {char* pw_shell; int /*<<< orphan*/  pw_name; } ;
typedef  TYPE_2__ Session ;

/* Variables and functions */
 scalar_t__ IS_INTERNAL_SFTP (char const*) ; 
 int /*<<< orphan*/  PRIVSEP (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBSYSTEM_EXT ; 
 scalar_t__ SUBSYSTEM_INT_SFTP ; 
 scalar_t__ SUBSYSTEM_INT_SFTP_ERROR ; 
 char* _PATH_BSHELL ; 
 int /*<<< orphan*/  audit_run_command (char const*) ; 
 TYPE_7__* auth_opts ; 
 int do_exec_no_pty (struct ssh*,TYPE_2__*,char const*) ; 
 int do_exec_pty (struct ssh*,TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  loginmsg ; 
 TYPE_3__ options ; 
 char const* original_command ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  ssh_remote_ipaddr (struct ssh*) ; 
 int /*<<< orphan*/  ssh_remote_port (struct ssh*) ; 
 int /*<<< orphan*/  sshbuf_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  verbose (char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
do_exec(struct ssh *ssh, Session *s, const char *command)
{
	int ret;
	const char *forced = NULL, *tty = NULL;
	char session_type[1024];

	if (options.adm_forced_command) {
		original_command = command;
		command = options.adm_forced_command;
		forced = "(config)";
	} else if (auth_opts->force_command != NULL) {
		original_command = command;
		command = auth_opts->force_command;
		forced = "(key-option)";
	}
	if (forced != NULL) {
		if (IS_INTERNAL_SFTP(command)) {
			s->is_subsystem = s->is_subsystem ?
			    SUBSYSTEM_INT_SFTP : SUBSYSTEM_INT_SFTP_ERROR;
		} else if (s->is_subsystem)
			s->is_subsystem = SUBSYSTEM_EXT;
		snprintf(session_type, sizeof(session_type),
		    "forced-command %s '%.900s'", forced, command);
	} else if (s->is_subsystem) {
		snprintf(session_type, sizeof(session_type),
		    "subsystem '%.900s'", s->subsys);
	} else if (command == NULL) {
		snprintf(session_type, sizeof(session_type), "shell");
	} else {
		/* NB. we don't log unforced commands to preserve privacy */
		snprintf(session_type, sizeof(session_type), "command");
	}

	if (s->ttyfd != -1) {
		tty = s->tty;
		if (strncmp(tty, "/dev/", 5) == 0)
			tty += 5;
	}

	verbose("Starting session: %s%s%s for %s from %.200s port %d id %d",
	    session_type,
	    tty == NULL ? "" : " on ",
	    tty == NULL ? "" : tty,
	    s->pw->pw_name,
	    ssh_remote_ipaddr(ssh),
	    ssh_remote_port(ssh),
	    s->self);

#ifdef SSH_AUDIT_EVENTS
	if (command != NULL)
		PRIVSEP(audit_run_command(command));
	else if (s->ttyfd == -1) {
		char *shell = s->pw->pw_shell;

		if (shell[0] == '\0')	/* empty shell means /bin/sh */
			shell =_PATH_BSHELL;
		PRIVSEP(audit_run_command(shell));
	}
#endif
	if (s->ttyfd != -1)
		ret = do_exec_pty(ssh, s, command);
	else
		ret = do_exec_no_pty(ssh, s, command);

	original_command = NULL;

	/*
	 * Clear loginmsg: it's the child's responsibility to display
	 * it to the user, otherwise multiple sessions may accumulate
	 * multiple copies of the login messages.
	 */
	sshbuf_reset(loginmsg);

	return ret;
}