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
 int /*<<< orphan*/  CMDLINE ; 
 int /*<<< orphan*/  addstr (char*) ; 
 int /*<<< orphan*/  clrtoeol () ; 
 int curscale ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 char* get_helplist () ; 
 int get_scale (char const*) ; 
 int /*<<< orphan*/ * matchline ; 
 scalar_t__ memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  move (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int needsort ; 
 scalar_t__ prefix (char const*,char*) ; 
 int showpps ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

int
ifcmd(const char *cmd, const char *args)
{
	int scale;

	if (prefix(cmd, "scale")) {
		if ((scale = get_scale(args)) != -1)
			curscale = scale;
		else {
			move(CMDLINE, 0);
			clrtoeol();
			addstr("what scale? ");
			addstr(get_helplist());
		}
	} else if (prefix(cmd, "match")) {
		if (args != NULL && *args != '\0' && memcmp(args, "*", 2) != 0) {
			/* We got a valid match line */
			if (matchline != NULL)
				free(matchline);
			needsort = 1;
			matchline = strdup(args);
		} else {
			/* Empty or * pattern, turn filtering off */
			if (matchline != NULL)
				free(matchline);
			needsort = 1;
			matchline = NULL;
		}
	} else if (prefix(cmd, "pps"))
		showpps = !showpps;

	return (1);
}