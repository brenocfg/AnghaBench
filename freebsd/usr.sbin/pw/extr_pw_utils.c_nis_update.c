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
typedef  int pid_t ;

/* Variables and functions */
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  execlp (char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int fork () ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
nis_update(void) {
	pid_t pid;
	int i;

	fflush(NULL);
	if ((pid = fork()) == -1) {
		warn("fork()");
		return (1);
	}
	if (pid == 0) {
		execlp("/usr/bin/make", "make", "-C", "/var/yp/", (char*) NULL);
		_exit(1);
	}
	waitpid(pid, &i, 0);
	if ((i = WEXITSTATUS(i)) != 0)
		errx(i, "make exited with status %d", i);
	return (i);
}