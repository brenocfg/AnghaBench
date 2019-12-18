#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mouse_char; } ;
struct mouse_info {TYPE_1__ u; int /*<<< orphan*/  operation; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONS_MOUSECTL ; 
 int /*<<< orphan*/  MOUSE_MOUSECHAR ; 
 int UCHAR_MAX ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mouse_info*) ; 
 int /*<<< orphan*/  revert () ; 
 long strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int) ; 

__attribute__((used)) static void
set_mouse_char(char *arg)
{
	struct mouse_info mouse;
	long l;

	l = strtol(arg, NULL, 0);

	if ((l < 0) || (l > UCHAR_MAX - 3)) {
		revert();
		warnx("argument to -M must be 0 through %d", UCHAR_MAX - 3);
		return;
	}

	mouse.operation = MOUSE_MOUSECHAR;
	mouse.u.mouse_char = (int)l;

	if (ioctl(0, CONS_MOUSECTL, &mouse) == -1) {
		revert();
		err(1, "setting mouse character");
	}
}