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
 int /*<<< orphan*/  VT_LOCKSWITCH ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  revert () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void
set_lockswitch(char *arg)
{
	int data;

	if (!strcmp(arg, "off")) {
		data = 0x01;
	} else if (!strcmp(arg, "on")) {
		data = 0x02;
	} else {
		revert();
		errx(1, "argument to -S must be either on or off");
	}

	if (ioctl(0, VT_LOCKSWITCH, &data) == -1) {
		revert();
		err(1, "turning %s vty switching",
		     data == 0x01 ? "off" : "on");
	}
}