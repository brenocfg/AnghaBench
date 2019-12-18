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
 int /*<<< orphan*/  CONS_BLANKTIME ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  revert () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void
set_screensaver_timeout(char *arg)
{
	int nsec;

	if (!strcmp(arg, "off")) {
		nsec = 0;
	} else {
		nsec = atoi(arg);

		if ((*arg == '\0') || (nsec < 1)) {
			revert();
			errx(1, "argument must be a positive number");
		}
	}

	if (ioctl(0, CONS_BLANKTIME, &nsec) == -1) {
		revert();
		err(1, "setting screensaver period");
	}
}