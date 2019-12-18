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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int*) ; 
 int getpid () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
check_pidfile(const char *path)
{
	FILE *file;
	int pid;

	printf("Validating contents of pidfile '%s'\n", path);

	if ((file = fopen(path, "r")) == NULL)
		errx(EXIT_FAILURE, "Cannot open expected pidfile '%s'", path);

	if (fscanf(file, "%d", &pid) == -1)
		errx(EXIT_FAILURE, "Failed to read pid from pidfile '%s'",
		    path);

	printf("Read pid %d, current pid %d\n", pid, getpid());
	if (pid != getpid())
		errx(EXIT_FAILURE, "Pid in pidfile (%d) does not match "
		    "current pid (%d)", pid, getpid());
}