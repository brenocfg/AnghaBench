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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  sig_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ECHOCHECK ; 
 int EOF ; 
 int /*<<< orphan*/  ETIMEOUT ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  PROMPT ; 
 int /*<<< orphan*/  RAWFTP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGIOT ; 
 int STRIP_PAR ; 
 int /*<<< orphan*/  TABEXPAND ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  alarm (unsigned int) ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccc ; 
 int character (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defchars ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fildes ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  prtime (char*,scalar_t__) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * repdes ; 
 int /*<<< orphan*/  send (char) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ stop ; 
 int /*<<< orphan*/  stopsnd ; 
 int /*<<< orphan*/  tcdrain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  term ; 
 scalar_t__ time (int /*<<< orphan*/ ) ; 
 scalar_t__ timedout ; 
 int /*<<< orphan*/  tipout_pid ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
transmit(FILE *fp, char *eofchars, char *command)
{
	char *pc, lastc;
	int c, ccount, lcount;
	time_t start_t, stop_t;
	sig_t f;

	kill(tipout_pid, SIGIOT);	/* put TIPOUT into a wait state */
	stop = 0;
	f = signal(SIGINT, stopsnd);
	tcsetattr(0, TCSAFLUSH, &defchars);
	read(repdes[0], (char *)&ccc, 1);
	if (command != NULL) {
		for (pc = command; *pc; pc++)
			send(*pc);
		if (boolean(value(ECHOCHECK)))
			read(FD, (char *)&c, 1);	/* trailing \n */
		else {
			tcdrain(FD);
			sleep(5); /* wait for remote stty to take effect */
		}
	}
	lcount = 0;
	lastc = '\0';
	start_t = time(0);
	while (1) {
		ccount = 0;
		do {
			c = getc(fp);
			if (stop)
				goto out;
			if (c == EOF)
				goto out;
			if (c == 0177 && !boolean(value(RAWFTP)))
				continue;
			lastc = c;
			if (c < 040) {
				if (c == '\n') {
					if (!boolean(value(RAWFTP)))
						c = '\r';
				} else if (c == '\t') {
					if (!boolean(value(RAWFTP))) {
						if (boolean(value(TABEXPAND))) {
							send(' ');
							while ((++ccount % 8) != 0)
								send(' ');
							continue;
						}
					}
				} else
					if (!boolean(value(RAWFTP)))
						continue;
			}
			send(c);
		} while (c != '\r' && !boolean(value(RAWFTP)));
		if (boolean(value(VERBOSE)))
			printf("\r%d", ++lcount);
		if (boolean(value(ECHOCHECK))) {
			timedout = 0;
			alarm((unsigned int)lvalue(ETIMEOUT));
			do {	/* wait for prompt */
				read(FD, (char *)&c, 1);
				if (timedout || stop) {
					if (timedout)
						printf("\r\ntimed out at eol\r\n");
					alarm(0);
					goto out;
				}
			} while ((c&STRIP_PAR) != character(value(PROMPT)));
			alarm(0);
		}
	}
out:
	if (lastc != '\n' && !boolean(value(RAWFTP)))
		send('\r');
	if (eofchars) {
		for (pc = eofchars; *pc; pc++)
			send(*pc);
	}
	stop_t = time(0);
	fclose(fp);
	signal(SIGINT, f);
	if (boolean(value(VERBOSE))) {
		if (boolean(value(RAWFTP)))
			prtime(" chars transferred in ", stop_t-start_t);
		else
			prtime(" lines transferred in ", stop_t-start_t);
	}
	write(fildes[1], (char *)&ccc, 1);
	tcsetattr(0, TCSAFLUSH, &term);
}