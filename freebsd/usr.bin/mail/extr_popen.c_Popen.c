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
typedef  int /*<<< orphan*/  sigset_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFD ; 
 size_t READ ; 
 size_t WRITE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * fdopen (int,char const*) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  register_file (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ start_command (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  value (char*) ; 

FILE *
Popen(char *cmd, const char *mode)
{
	int p[2];
	int myside, hisside, fd0, fd1;
	pid_t pid;
	sigset_t nset;
	FILE *fp;

	if (pipe(p) < 0)
		return (NULL);
	(void)fcntl(p[READ], F_SETFD, 1);
	(void)fcntl(p[WRITE], F_SETFD, 1);
	if (*mode == 'r') {
		myside = p[READ];
		hisside = fd0 = fd1 = p[WRITE];
	} else {
		myside = p[WRITE];
		hisside = fd0 = p[READ];
		fd1 = -1;
	}
	(void)sigemptyset(&nset);
	pid = start_command(value("SHELL"), &nset, fd0, fd1, "-c", cmd, NULL);
	if (pid < 0) {
		(void)close(p[READ]);
		(void)close(p[WRITE]);
		return (NULL);
	}
	(void)close(hisside);
	if ((fp = fdopen(myside, mode)) != NULL)
		register_file(fp, 1, pid);
	return (fp);
}