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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  execve (char*,char**,char**) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  sleep (int) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  wait (int*) ; 

__attribute__((used)) static int
child(void)
{
	pid_t ch;
	int status;
	char *argv[] = { NULL, NULL };
	char *envp[] = { NULL, NULL };

	if ((argv[0] = strdup("true")) == NULL)
		err(EXIT_FAILURE, "strdup(\"true\")");

	if ((envp[0] = strdup("FOO=BAZ")) == NULL)
		err(EXIT_FAILURE, "strdup(\"FOO=BAZ\")");

	/* Ensure parent is ready */
	(void)sleep(2);

	/* Do fork */
	switch (ch = fork()) {
	case -1:
		return EXIT_FAILURE;
		/* NOTREACHED */
	case 0:
		return EXIT_SUCCESS;
		/* NOTREACHED */
	default:
		wait(&status);
		break;
	}

	/* Exec */
	execve("/usr/bin/true", argv, envp);

	/* NOTREACHED */
	return EXIT_FAILURE;
}