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
 int ifcmd (char const*,char const*) ; 
 int /*<<< orphan*/  labelifstat () ; 
 scalar_t__ needclear ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  showifstat () ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wnd ; 

int
cmdifstat(const char *cmd, const char *args)
{
	int	retval = 0;

	retval = ifcmd(cmd, args);
	/* ifcmd() returns 1 on success */
	if (retval == 1) {
		if (needclear) {
			showifstat();
			refresh();
			werase(wnd);
			labelifstat();
			needclear = 0;
		}
	}
	return (retval);
}