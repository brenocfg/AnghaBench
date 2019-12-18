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
struct mouse_info {scalar_t__ operation; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONS_MOUSECTL ; 
 scalar_t__ MOUSE_HIDE ; 
 scalar_t__ MOUSE_SHOW ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mouse_info*) ; 
 int /*<<< orphan*/  revert () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void
set_mouse(char *arg)
{
	struct mouse_info mouse;

	if (!strcmp(arg, "on")) {
		mouse.operation = MOUSE_SHOW;
	} else if (!strcmp(arg, "off")) {
		mouse.operation = MOUSE_HIDE;
	} else {
		revert();
		errx(1, "argument to -m must be either on or off");
	}

	if (ioctl(0, CONS_MOUSECTL, &mouse) == -1) {
		revert();
		err(1, "%sing the mouse",
		     mouse.operation == MOUSE_SHOW ? "show" : "hid");
	}
}