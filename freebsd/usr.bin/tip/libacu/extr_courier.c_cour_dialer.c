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
struct termios {int /*<<< orphan*/  c_cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIALTIMEOUT ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  HOST ; 
 int /*<<< orphan*/  HUPCL ; 
 int /*<<< orphan*/  TCIOFLUSH ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  VERBOSE ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int connected ; 
 int cour_connect () ; 
 int /*<<< orphan*/  cour_disconnect () ; 
 int /*<<< orphan*/  cour_swallow (char*) ; 
 int /*<<< orphan*/  cour_verbose_read () ; 
 int /*<<< orphan*/  cour_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  coursync () ; 
 scalar_t__ dialtimeout ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logent (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  tcflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 

int
cour_dialer(char *num, char *acu)
{
	char *cp;
#ifdef ACULOG
	char line[80];
#endif
	struct termios cntrl;

	if (boolean(value(VERBOSE)))
		printf("Using \"%s\"\n", acu);

	tcgetattr(FD, &cntrl);
	cntrl.c_cflag |= HUPCL;
	tcsetattr(FD, TCSAFLUSH, &cntrl);
	/*
	 * Get in synch.
	 */
	if (!coursync()) {
badsynch:
		printf("can't synchronize with courier\n");
#ifdef ACULOG
		logent(value(HOST), num, "courier", "can't synch up");
#endif
		return (0);
	}
	cour_write(FD, "AT E0\r", 6);	/* turn off echoing */
	sleep(1);
#ifdef DEBUG
	if (boolean(value(VERBOSE)))
		cour_verbose_read();
#endif
	tcflush(FD, TCIOFLUSH);
	cour_write(FD, "AT C1 E0 H0 Q0 X6 V1\r", 21);
	if (!cour_swallow("\r\nOK\r\n"))
		goto badsynch;
	fflush(stdout);
	cour_write(FD, "AT D", 4);
	for (cp = num; *cp; cp++)
		if (*cp == '=')
			*cp = ',';
	cour_write(FD, num, strlen(num));
	cour_write(FD, "\r", 1);
	connected = cour_connect();
#ifdef ACULOG
	if (dialtimeout) {
		(void)snprintf(line, sizeof line, "%ld second dial timeout",
			number(value(DIALTIMEOUT)));
		logent(value(HOST), num, "cour", line);
	}
#endif
	if (dialtimeout)
		cour_disconnect();
	return (connected);
}