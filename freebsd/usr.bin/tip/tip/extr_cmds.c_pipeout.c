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
typedef  scalar_t__ time_t ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGIOT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  VERBOSE ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccc ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  defchars ; 
 int /*<<< orphan*/  dup2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  execute (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fildes ; 
 int fork () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ prompt (char*,char*,int) ; 
 int /*<<< orphan*/  prtime (char*,scalar_t__) ; 
 int /*<<< orphan*/  putchar (int) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * repdes ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  term ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipout_pid ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 
 int wait (int*) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

void
pipeout(int c)
{
	char buf[256];
	int status, p;
	pid_t cpid;
	time_t start = time(NULL);

	putchar(c);
	if (prompt("Local command? ", buf, sizeof(buf)))
		return;
	kill(tipout_pid, SIGIOT);	/* put TIPOUT into a wait state */
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	tcsetattr(0, TCSAFLUSH, &defchars);
	read(repdes[0], (char *)&ccc, 1);
	/*
	 * Set up file descriptors in the child and
	 *  let it go...
	 */
	if ((cpid = fork()) < 0)
		printf("can't fork!\r\n");
	else if (cpid) {
		start = time(NULL);
		while ((p = wait(&status)) > 0 && p != cpid)
			;
	} else {
		int i;

		dup2(FD, 1);
		for (i = 3; i < 20; i++)
			close(i);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execute(buf);
		printf("can't find `%s'\r\n", buf);
		exit(0);
	}
	if (boolean(value(VERBOSE)))
		prtime("away for ", time(0)-start);
	write(fildes[1], (char *)&ccc, 1);
	tcsetattr(0, TCSAFLUSH, &term);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}