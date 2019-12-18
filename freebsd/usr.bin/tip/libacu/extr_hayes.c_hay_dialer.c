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
 int /*<<< orphan*/  CONNECTED ; 
 int /*<<< orphan*/  DIALING ; 
 int /*<<< orphan*/  DIALTIMEOUT ; 
 int /*<<< orphan*/  FAILED ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  HOST ; 
 int /*<<< orphan*/  HUPCL ; 
 int /*<<< orphan*/  TCIOFLUSH ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  VERBOSE ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 scalar_t__ dialtimeout ; 
 int /*<<< orphan*/  error_rep (char) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char gobble (char*) ; 
 int /*<<< orphan*/  hay_disconnect () ; 
 scalar_t__ hay_sync () ; 
 int /*<<< orphan*/  logent (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  tcflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

int
hay_dialer(char *num, char *acu)
{
	char *cp;
	int connected = 0;
	char dummy;
	struct termios cntrl;
#ifdef ACULOG
	char line[80];
#endif
	if (hay_sync() == 0)		/* make sure we can talk to the modem */
		return(0);
	if (boolean(value(VERBOSE)))
		printf("\ndialing...");
	fflush(stdout);
	tcgetattr(FD, &cntrl);
	cntrl.c_cflag |= HUPCL;
	tcsetattr(FD, TCSANOW, &cntrl);
	tcflush(FD, TCIOFLUSH);
	write(FD, "ATv0\r", 5);	/* tell modem to use short status codes */
	gobble("\r");
	gobble("\r");
	write(FD, "ATTD", 4);	/* send dial command */
	for (cp = num; *cp; cp++)
		if (*cp == '=')
			*cp = ',';
	write(FD, num, strlen(num));
	state = DIALING;
	write(FD, "\r", 1);
	connected = 0;
	if (gobble("\r")) {
		if ((dummy = gobble("01234")) != '1')
			error_rep(dummy);
		else
			connected = 1;
	}
	if (connected)
		state = CONNECTED;
	else {
		state = FAILED;
		return (connected);	/* lets get out of here.. */
	}
	tcflush(FD, TCIOFLUSH);
#ifdef ACULOG
	if (dialtimeout) {
		(void)snprintf(line, sizeof line, "%ld second dial timeout",
			number(value(DIALTIMEOUT)));
		logent(value(HOST), num, "hayes", line);
	}
#endif
	if (dialtimeout)
		hay_disconnect();	/* insurance */
	return (connected);
}