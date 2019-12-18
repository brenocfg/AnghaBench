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

/* Variables and functions */
 scalar_t__ WCOREDUMP (int /*<<< orphan*/ ) ; 
 scalar_t__ WIFSIGNALED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  wait_child (int) ; 
 int /*<<< orphan*/  wait_status ; 
 int /*<<< orphan*/  warn (char*) ; 

int
core(void)
{
	int pid;

	switch (pid = fork()) {
	case -1:
		warn("fork");
		return (1);
	case 0:
		abort();
		_exit(1);
	}
	printf("Okie dokie");
	(void)fflush(stdout);
	wait_child(pid);
	if (WIFSIGNALED(wait_status) && WCOREDUMP(wait_status))
		printf(" -- Core dumped.\n");
	else
		printf(" -- Can't dump core.\n");
	return (0);
}