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
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 char* onoff (int) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  ttyout ; 

int
togglevar(int argc, char *argv[], int *var, const char *mesg)
{
	if (argc == 1) {
		*var = !*var;
	} else if (argc == 2 && strcasecmp(argv[1], "on") == 0) {
		*var = 1;
	} else if (argc == 2 && strcasecmp(argv[1], "off") == 0) {
		*var = 0;
	} else {
		UPRINTF("usage: %s [ on | off ]\n", argv[0]);
		return (-1);
	}
	if (mesg)
		fprintf(ttyout, "%s %s.\n", mesg, onoff(*var));
	return (*var);
}