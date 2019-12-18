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
 int color_stdout_is_tty ; 
 int /*<<< orphan*/  is_terminal_dumb () ; 
 int isatty (int) ; 
 scalar_t__ pager_in_use () ; 
 scalar_t__ pager_use_color ; 

__attribute__((used)) static int check_auto_color(int fd)
{
	static int color_stderr_is_tty = -1;
	int *is_tty_p = fd == 1 ? &color_stdout_is_tty : &color_stderr_is_tty;
	if (*is_tty_p < 0)
		*is_tty_p = isatty(fd);
	if (*is_tty_p || (fd == 1 && pager_in_use() && pager_use_color)) {
		if (!is_terminal_dumb())
			return 1;
	}
	return 0;
}