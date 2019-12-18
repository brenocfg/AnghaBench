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
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  VERBOSE ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int connected ; 
 scalar_t__ dialtimeout ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logent (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 
 int t3000_connect () ; 
 int /*<<< orphan*/  t3000_disconnect () ; 
 int /*<<< orphan*/  t3000_swallow (char*) ; 
 int /*<<< orphan*/  t3000_sync () ; 
 int /*<<< orphan*/  t3000_verbose_read () ; 
 int /*<<< orphan*/  t3000_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tcflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 

int
t3000_dialer(char *num, char *acu)
{
	char *cp;
	struct termios cntrl;
#ifdef ACULOG
	char line[80];
#endif

	if (boolean(value(VERBOSE)))
		printf("Using \"%s\"\n", acu);

	tcgetattr(FD, &cntrl);
	cntrl.c_cflag |= HUPCL;
	tcsetattr(FD, TCSANOW, &cntrl);
	/*
	 * Get in synch.
	 */
	if (!t3000_sync()) {
badsynch:
		printf("can't synchronize with t3000\n");
#ifdef ACULOG
		logent(value(HOST), num, "t3000", "can't synch up");
#endif
		return (0);
	}
	t3000_write(FD, "AT E0\r", 6);	/* turn off echoing */
	sleep(1);
#ifdef DEBUG
	if (boolean(value(VERBOSE)))
		t3000_verbose_read();
#endif
	tcflush(FD, TCIOFLUSH);
	t3000_write(FD, "AT E0 H0 Q0 X4 V1\r", 18);
	if (!t3000_swallow("\r\nOK\r\n"))
		goto badsynch;
	fflush(stdout);
	t3000_write(FD, "AT D", 4);
	for (cp = num; *cp; cp++)
		if (*cp == '=')
			*cp = ',';
	t3000_write(FD, num, strlen(num));
	t3000_write(FD, "\r", 1);
	connected = t3000_connect();
#ifdef ACULOG
	if (dialtimeout) {
		(void)snprintf(line, sizeof line, "%ld second dial timeout",
			number(value(DIALTIMEOUT)));
		logent(value(HOST), num, "t3000", line);
	}
#endif
	if (dialtimeout)
		t3000_disconnect();
	return (connected);
}