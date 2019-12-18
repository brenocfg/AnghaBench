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
 int /*<<< orphan*/  delay (int,int) ; 
 scalar_t__ dialtimeout ; 
 int /*<<< orphan*/  echo (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int gobble (char,char*) ; 
 scalar_t__ isupper (char) ; 
 int /*<<< orphan*/  logent (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  tcflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 char tolower (char) ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ven_disconnect () ; 
 int /*<<< orphan*/  vensync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

int
ven_dialer(char *num, char *acu)
{
	char *cp;
	int connected = 0;
	char *msg, line[80];
	struct termios	cntrl;

	/*
	 * Get in synch with a couple of carriage returns
	 */
	if (!vensync(FD)) {
		printf("can't synchronize with ventel\n");
#ifdef ACULOG
		logent(value(HOST), num, "ventel", "can't synch up");
#endif
		return (0);
	}
	if (boolean(value(VERBOSE)))
		printf("\ndialing...");
	fflush(stdout);
	tcgetattr(FD, &cntrl);
	cntrl.c_cflag |= HUPCL;
	tcsetattr(FD, TCSANOW, &cntrl);
	echo("#k$\r$\n$D$I$A$L$:$ ");
	for (cp = num; *cp; cp++) {
		delay(1, 10);
		write(FD, cp, 1);
	}
	delay(1, 10);
	write(FD, "\r", 1);
	gobble('\n', line);
	if (gobble('\n', line))
		connected = gobble('!', line);
	tcflush(FD, TCIOFLUSH);
#ifdef ACULOG
	if (dialtimeout) {
		(void)snprintf(line, sizeof line, "%ld second dial timeout",
			number(value(DIALTIMEOUT)));
		logent(value(HOST), num, "ventel", line);
	}
#endif
	if (dialtimeout)
		ven_disconnect();	/* insurance */
	if (connected || dialtimeout || !boolean(value(VERBOSE)))
		return (connected);
	/* call failed, parse response for user */
	cp = strchr(line, '\r');
	if (cp)
		*cp = '\0';
	for (cp = line; (cp = strchr(cp, ' ')) != NULL; cp++)
		if (cp[1] == ' ')
			break;
	if (cp) {
		while (*cp == ' ')
			cp++;
		msg = cp;
		while (*cp) {
			if (isupper(*cp))
				*cp = tolower(*cp);
			cp++;
		}
		printf("%s...", msg);
	}
	return (connected);
}