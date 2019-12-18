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
 int /*<<< orphan*/  SO_DEBUG ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int code ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int ftp_debug ; 
 char* onoff (int) ; 
 int /*<<< orphan*/  options ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int strsuftoi (char*) ; 
 int /*<<< orphan*/  ttyout ; 

void
setdebug(int argc, char *argv[])
{
	if (argc == 0 || argc > 2) {
		UPRINTF("usage: %s [ on | off | debuglevel ]\n", argv[0]);
		code = -1;
		return;
	} else if (argc == 2) {
		if (strcasecmp(argv[1], "on") == 0)
			ftp_debug = 1;
		else if (strcasecmp(argv[1], "off") == 0)
			ftp_debug = 0;
		else {
			int val;

			val = strsuftoi(argv[1]);
			if (val < 0) {
				fprintf(ttyout, "%s: bad debugging value.\n",
				    argv[1]);
				code = -1;
				return;
			}
			ftp_debug = val;
		}
	} else
		ftp_debug = !ftp_debug;
	if (ftp_debug)
		options |= SO_DEBUG;
	else
		options &= ~SO_DEBUG;
	fprintf(ttyout, "Debugging %s (ftp_debug=%d).\n", onoff(ftp_debug), ftp_debug);
	code = ftp_debug > 0;
}