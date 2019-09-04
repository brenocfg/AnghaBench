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
 int WM_CASEFOLD ; 
 int WM_PATHNAME ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  wildmatch (char const*,char const*,int) ; 

int cmd__wildmatch(int argc, const char **argv)
{
	int i;
	for (i = 2; i < argc; i++) {
		if (argv[i][0] == '/')
			die("Forward slash is not allowed at the beginning of the\n"
			    "pattern because Windows does not like it. Use `XXX/' instead.");
		else if (!strncmp(argv[i], "XXX/", 4))
			argv[i] += 3;
	}
	if (!strcmp(argv[1], "wildmatch"))
		return !!wildmatch(argv[3], argv[2], WM_PATHNAME);
	else if (!strcmp(argv[1], "iwildmatch"))
		return !!wildmatch(argv[3], argv[2], WM_PATHNAME | WM_CASEFOLD);
	else if (!strcmp(argv[1], "pathmatch"))
		return !!wildmatch(argv[3], argv[2], 0);
	else if (!strcmp(argv[1], "ipathmatch"))
		return !!wildmatch(argv[3], argv[2], WM_CASEFOLD);
	else
		return 1;
}