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
 int /*<<< orphan*/  act (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  setup (int) ; 
 int /*<<< orphan*/ * stk ; 
 int /*<<< orphan*/ * tmpstk ; 

int
main(int argc, char *argv[])
{
	int child;

	if (argc != 2) {
		printf(
	    "Usage: popss [bound|int1|int3|into|int80|syscall|sysenter]\n");
		exit(1);
	}
	stk = &tmpstk[nitems(tmpstk) - 1];
	child = fork();
	if (child == -1)
		err(1, "fork");
	if (child == 0)
		act(argv[1]);
	else
		setup(child);
}