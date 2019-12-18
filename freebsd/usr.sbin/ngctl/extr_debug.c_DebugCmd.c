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
 int CMDRTN_OK ; 
 int CMDRTN_USAGE ; 
 int NgSetDebug (int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int
DebugCmd(int ac, char **av)
{
	int level;

	/* Get arguments */
	switch (ac) {
	case 2:
		if (!strcmp(av[1], "+"))
			level = NgSetDebug(-1) + 1;
		else if (!strcmp(av[1], "-"))
			level = NgSetDebug(-1) - 1;
		else if ((level = atoi(av[1])) < 0)
			return (CMDRTN_USAGE);
		NgSetDebug(level);
		break;
	case 1:
		printf("Current debug level is %d\n", NgSetDebug(-1));
		break;
	default:
		return (CMDRTN_USAGE);
	}
	return (CMDRTN_OK);
}