#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
typedef  int pid_t ;
struct TYPE_3__ {scalar_t__ num; int /*<<< orphan*/ * list; } ;
typedef  TYPE_1__ arglist ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int do_cmd_pid ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execvp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  fmprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  killchild ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ verbose_mode ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_local_cmd(arglist *a)
{
	u_int i;
	int status;
	pid_t pid;

	if (a->num == 0)
		fatal("do_local_cmd: no arguments");

	if (verbose_mode) {
		fprintf(stderr, "Executing:");
		for (i = 0; i < a->num; i++)
			fmprintf(stderr, " %s", a->list[i]);
		fprintf(stderr, "\n");
	}
	if ((pid = fork()) == -1)
		fatal("do_local_cmd: fork: %s", strerror(errno));

	if (pid == 0) {
		execvp(a->list[0], a->list);
		perror(a->list[0]);
		exit(1);
	}

	do_cmd_pid = pid;
	signal(SIGTERM, killchild);
	signal(SIGINT, killchild);
	signal(SIGHUP, killchild);

	while (waitpid(pid, &status, 0) == -1)
		if (errno != EINTR)
			fatal("do_local_cmd: waitpid: %s", strerror(errno));

	do_cmd_pid = -1;

	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		return (-1);

	return (0);
}