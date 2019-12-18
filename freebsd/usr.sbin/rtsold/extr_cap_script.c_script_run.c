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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 scalar_t__ STDIN_FILENO ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closefrom (int) ; 
 scalar_t__ dup2 (int,scalar_t__) ; 
 int /*<<< orphan*/  execve (char*,char**,int /*<<< orphan*/ *) ; 
 scalar_t__ fork () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pipe (int*) ; 

__attribute__((used)) static int
script_run(char **argv)
{
	pid_t pid;
	int fd[2], null;

	if (pipe(fd) != 0)
		return (-1);
	if ((pid = fork()) < 0)
		return (-1);
	if (pid == 0) {
		(void)close(fd[1]);
		null = open("/dev/null", O_RDWR);
		if (null < 0)
			_exit(1);
		if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
			_exit(1);

		closefrom(3);
		(void)execve(argv[0], argv, NULL);
		_exit(1);
	} else
		(void)close(fd[0]);

	return (fd[1]);
}