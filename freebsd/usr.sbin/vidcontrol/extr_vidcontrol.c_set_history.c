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
 int /*<<< orphan*/  CONS_HISTORY ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  revert () ; 

__attribute__((used)) static void
set_history(char *opt)
{
	int size;

	size = atoi(opt);

	if ((*opt == '\0') || size < 0) {
		revert();
		errx(1, "argument must not be less than zero");
	}

	if (ioctl(0, CONS_HISTORY, &size) == -1) {
		revert();
		err(1, "setting history buffer size");
	}
}