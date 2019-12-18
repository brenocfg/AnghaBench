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
typedef  int /*<<< orphan*/  cbuf ;

/* Variables and functions */
 int /*<<< orphan*/  DIALTIMEOUT ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  HOST ; 
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  biz22_disconnect () ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 scalar_t__ cmd (char*) ; 
 int detect (char*) ; 
 scalar_t__ dialtimeout ; 
 int /*<<< orphan*/  logent (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
biz_dialer(char *num, char *mod)
{
	int connected = 0;
	char cbuf[40];

	if (boolean(value(VERBOSE)))
		printf("\nstarting call...");
	/*
	 * Disable auto-answer and configure for tone/pulse
	 *  dialing
	 */
	if (cmd("\02K\r")) {
		printf("can't initialize bizcomp...");
		return (0);
	}
	(void)strlcpy(cbuf, "\02.\r", sizeof cbuf);
	cbuf[1] = *mod;
	if (cmd(cbuf)) {
		printf("can't set dialing mode...");
		return (0);
	}
	(void)snprintf(cbuf, sizeof(cbuf), "\02D%s\r", num);
	write(FD, cbuf, strlen(cbuf));
	if (!detect("7\r")) {
		printf("can't get dial tone...");
		return (0);
	}
	if (boolean(value(VERBOSE)))
		printf("ringing...");
	/*
	 * The reply from the BIZCOMP should be:
	 *	2 \r or 7 \r	failure
	 *	1 \r		success
	 */
	connected = detect("1\r");
#ifdef ACULOG
	if (dialtimeout) {
		char line[80];

		(void)snprintf(line, sizeof line, "%ld second dial timeout",
			number(value(DIALTIMEOUT)));
		logent(value(HOST), num, "biz1022", line);
	}
#endif
	if (dialtimeout)
		biz22_disconnect();	/* insurance */
	return (connected);
}