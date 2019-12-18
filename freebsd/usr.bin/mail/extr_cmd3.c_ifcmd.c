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
 scalar_t__ CANY ; 
 scalar_t__ CRCV ; 
 scalar_t__ CSEND ; 
 scalar_t__ cond ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
ifcmd(char **argv)
{
	char *cp;

	if (cond != CANY) {
		printf("Illegal nested \"if\"\n");
		return (1);
	}
	cond = CANY;
	cp = argv[0];
	switch (*cp) {
	case 'r': case 'R':
		cond = CRCV;
		break;

	case 's': case 'S':
		cond = CSEND;
		break;

	default:
		printf("Unrecognized if-keyword: \"%s\"\n", cp);
		return (1);
	}
	return (0);
}