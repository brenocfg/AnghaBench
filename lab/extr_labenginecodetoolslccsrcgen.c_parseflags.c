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
 int bflag ; 
 int dflag ; 
 scalar_t__ strcmp (char*,char*) ; 

void parseflags(int argc, char *argv[]) {
	int i;

	for (i = 0; i < argc; i++)
		if (strcmp(argv[i], "-d") == 0)
			dflag = 1;
		else if (strcmp(argv[i], "-b") == 0)	/* omit */
			bflag = 1;			/* omit */
}