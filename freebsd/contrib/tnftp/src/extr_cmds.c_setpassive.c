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
 int activefallback ; 
 int code ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* onoff (int) ; 
 int passivemode ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  ttyout ; 

void
setpassive(int argc, char *argv[])
{

	if (argc == 1) {
		passivemode = !passivemode;
		activefallback = passivemode;
	} else if (argc != 2) {
 passiveusage:
		UPRINTF("usage: %s [ on | off | auto ]\n", argv[0]);
		code = -1;
		return;
	} else if (strcasecmp(argv[1], "on") == 0) {
		passivemode = 1;
		activefallback = 0;
	} else if (strcasecmp(argv[1], "off") == 0) {
		passivemode = 0;
		activefallback = 0;
	} else if (strcasecmp(argv[1], "auto") == 0) {
		passivemode = 1;
		activefallback = 1;
	} else
		goto passiveusage;
	fprintf(ttyout, "Passive mode: %s; fallback to active mode: %s.\n",
	    onoff(passivemode), onoff(activefallback));
	code = passivemode;
}