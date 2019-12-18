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
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  bar () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__ kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int saw ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usr1 ; 

int
main(int argc, char **argv)
{

	bar(); /* force the symbol to be emitted */

	if (argc == 1)
		return (EXIT_SUCCESS);
	if (argc == 2 && strcmp(argv[1], "-s") == 0) {
		if (signal(SIGUSR1, usr1) == SIG_ERR)
			err(1, "signal");
		if (kill(getpid(), SIGUSR1) != 0)
			err(1, "kill");
		return (saw == 1 ? EXIT_SUCCESS : EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}