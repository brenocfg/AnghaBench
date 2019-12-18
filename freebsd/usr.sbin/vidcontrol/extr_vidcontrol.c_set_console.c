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
 int /*<<< orphan*/  VT_ACTIVATE ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  revert () ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strspn (char*,char*) ; 

__attribute__((used)) static void
set_console(char *arg)
{
	int n;

	if(!arg || strspn(arg,"0123456789") != strlen(arg)) {
		revert();
		errx(1, "bad console number");
	}

	n = atoi(arg);

	if (n < 1 || n > 16) {
		revert();
		errx(1, "console number out of range");
	} else if (ioctl(0, VT_ACTIVATE, n) == -1) {
		revert();
		err(1, "switching vty");
	}
}