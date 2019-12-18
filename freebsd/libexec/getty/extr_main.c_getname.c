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
 int CTRL (unsigned char) ; 
 int EOT ; 
 int ERASE ; 
 scalar_t__ IG ; 
 int KILL ; 
 int /*<<< orphan*/  LC ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ PF ; 
 scalar_t__ PP ; 
 unsigned char PPP_CONTROL ; 
 unsigned char PPP_CONTROL_ESCAPED ; 
 unsigned char PPP_ESCAPE ; 
 unsigned char PPP_FRAME ; 
 unsigned char PPP_LCP_HI ; 
 unsigned char PPP_LCP_LOW ; 
 unsigned char PPP_STATION ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  TCSANOW ; 
 scalar_t__ UC ; 
 int cfgetospeed (int /*<<< orphan*/ *) ; 
 int crmod ; 
 int digit ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  interrupt ; 
 int /*<<< orphan*/  intrupt ; 
 scalar_t__ isdigit (int) ; 
 scalar_t__ islower (int) ; 
 scalar_t__ isupper (char) ; 
 int lower ; 
 char* name ; 
 int /*<<< orphan*/  oflush () ; 
 int /*<<< orphan*/  prompt () ; 
 int /*<<< orphan*/  putchr (unsigned char) ; 
 int /*<<< orphan*/  putf (char*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 scalar_t__ read (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  set_flags (int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (scalar_t__) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmode ; 
 char tolower (char) ; 
 int /*<<< orphan*/  ttyn ; 
 int upper ; 

__attribute__((used)) static int
getname(void)
{
	int c;
	char *np;
	unsigned char cs;
	int ppp_state = 0;
	int ppp_connection = 0;

	/*
	 * Interrupt may happen if we use CBREAK mode
	 */
	if (setjmp(intrupt)) {
		signal(SIGINT, SIG_IGN);
		return (0);
	}
	signal(SIGINT, interrupt);
	set_flags(1);
	prompt();
	oflush();
	if (PF > 0) {
		sleep(PF);
		PF = 0;
	}
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tmode) < 0) {
		syslog(LOG_ERR, "%s: %m", ttyn);
		exit(1);
	}
	crmod = digit = lower = upper = 0;
	np = name;
	for (;;) {
		oflush();
		if (read(STDIN_FILENO, &cs, 1) <= 0)
			exit(0);
		if ((c = cs&0177) == 0)
			return (0);

		/* PPP detection state machine..
		   Look for sequences:
		   PPP_FRAME, PPP_STATION, PPP_ESCAPE, PPP_CONTROL_ESCAPED or
		   PPP_FRAME, PPP_STATION, PPP_CONTROL (deviant from RFC)
		   See RFC1662.
		   Derived from code from Michael Hancock, <michaelh@cet.co.jp>
		   and Erik 'PPP' Olson, <eriko@wrq.com>
		 */

		if (PP && (cs == PPP_FRAME)) {
			ppp_state = 1;
		} else if (ppp_state == 1 && cs == PPP_STATION) {
			ppp_state = 2;
		} else if (ppp_state == 2 && cs == PPP_ESCAPE) {
			ppp_state = 3;
		} else if ((ppp_state == 2 && cs == PPP_CONTROL)
			|| (ppp_state == 3 && cs == PPP_CONTROL_ESCAPED)) {
			ppp_state = 4;
		} else if (ppp_state == 4 && cs == PPP_LCP_HI) {
			ppp_state = 5;
		} else if (ppp_state == 5 && cs == PPP_LCP_LOW) {
			ppp_connection = 1;
			break;
		} else {
			ppp_state = 0;
		}

		if (c == EOT || c == CTRL('d'))
			exit(0);
		if (c == '\r' || c == '\n' || np >= &name[sizeof name-1]) {
			putf("\r\n");
			break;
		}
		if (islower(c))
			lower = 1;
		else if (isupper(c))
			upper = 1;
		else if (c == ERASE || c == '\b' || c == 0177) {
			if (np > name) {
				np--;
				if (cfgetospeed(&tmode) >= 1200)
					puts("\b \b");
				else
					putchr(cs);
			}
			continue;
		} else if (c == KILL || c == CTRL('u')) {
			putchr('\r');
			if (cfgetospeed(&tmode) < 1200)
				putchr('\n');
			/* this is the way they do it down under ... */
			else if (np > name)
				puts("                                     \r");
			prompt();
			digit = lower = upper = 0;
			np = name;
			continue;
		} else if (isdigit(c))
			digit = 1;
		if (IG && (c <= ' ' || c > 0176))
			continue;
		*np++ = c;
		putchr(cs);
	}
	signal(SIGINT, SIG_IGN);
	*np = 0;
	if (c == '\r')
		crmod = 1;
	if ((upper && !lower && !LC) || UC)
		for (np = name; *np; np++)
			if (isupper(*np))
				*np = tolower(*np);
	return (1 + ppp_connection);
}