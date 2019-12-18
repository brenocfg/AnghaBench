#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int pid_t ;
struct TYPE_4__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  addargs (TYPE_1__*,char*,...) ; 
 TYPE_1__ args ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execvp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int fork () ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replacearg (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_program ; 
 int sshport ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ verbose_mode ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

int
do_cmd2(char *host, char *remuser, int port, char *cmd, int fdin, int fdout)
{
	pid_t pid;
	int status;

	if (verbose_mode)
		fmprintf(stderr,
		    "Executing: 2nd program %s host %s, user %s, command %s\n",
		    ssh_program, host,
		    remuser ? remuser : "(unspecified)", cmd);

	if (port == -1)
		port = sshport;

	/* Fork a child to execute the command on the remote host using ssh. */
	pid = fork();
	if (pid == 0) {
		dup2(fdin, 0);
		dup2(fdout, 1);

		replacearg(&args, 0, "%s", ssh_program);
		if (port != -1) {
			addargs(&args, "-p");
			addargs(&args, "%d", port);
		}
		if (remuser != NULL) {
			addargs(&args, "-l");
			addargs(&args, "%s", remuser);
		}
		addargs(&args, "--");
		addargs(&args, "%s", host);
		addargs(&args, "%s", cmd);

		execvp(ssh_program, args.list);
		perror(ssh_program);
		exit(1);
	} else if (pid == -1) {
		fatal("fork: %s", strerror(errno));
	}
	while (waitpid(pid, &status, 0) == -1)
		if (errno != EINTR)
			fatal("do_cmd2: waitpid: %s", strerror(errno));
	return 0;
}