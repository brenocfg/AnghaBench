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
struct rumpclient_fork {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  TESTSLEN ; 
 int /*<<< orphan*/  TESTSTR ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int fork () ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int rump_sys_pipe (int*) ; 
 int /*<<< orphan*/  rump_sys_read (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rump_sys_write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rumpclient_fork_init (struct rumpclient_fork*) ; 
 struct rumpclient_fork* rumpclient_prefork () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int wait (int*) ; 

__attribute__((used)) static void
pipecomm(void)
{
	struct rumpclient_fork *rf;
	char buf[TESTSLEN+1];
	int pipetti[2];
	int status;

	if (rump_sys_pipe(pipetti) == -1)
		errx(1, "pipe");

	if ((rf = rumpclient_prefork()) == NULL)
		err(1, "prefork");

	switch (fork()) {
	case -1:
		err(1, "fork");
		break;
	case 0:
		if (rumpclient_fork_init(rf) == -1)
			err(1, "postfork init failed");

		memset(buf, 0, sizeof(buf));
		if (rump_sys_read(pipetti[0], buf, TESTSLEN) != TESTSLEN)
			err(1, "pipe read");
		if (strcmp(TESTSTR, buf) != 0)
			errx(1, "teststring doesn't match, got %s", buf);
		break;
	default:
		if (rump_sys_write(pipetti[1], TESTSTR, TESTSLEN) != TESTSLEN)
			err(1, "pipe write");
		if (wait(&status) == -1)
			err(1, "wait failed");
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			errx(1, "child exited with status %d", status);
		break;
	}
}