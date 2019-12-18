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
 int EAGAIN ; 
 int EINTR ; 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WUNTRACED ; 
 int errno ; 
 int /*<<< orphan*/  execv (char* const,char* const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
shell_out(char * const argv[])
{
	int status, piderr;
	pid_t pid;

	pid = fork();

	if (pid < 0) {
		fprintf(stderr,
			"System error: `fork()` call failed (%d) - %s\n",
			errno, strerror(errno));
		exit(-1);
	}

	if (pid == 0) {
		execv(argv[0], argv);
	}

	do {
		piderr = waitpid(pid, &status, WUNTRACED);
	} while (piderr < 0 && (errno == EAGAIN || errno == EINTR));

	return WEXITSTATUS(status);
}