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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  DIALTIMEOUT ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  Sjbuf ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  alarmtr ; 
 scalar_t__ notin (char*,char*) ; 
 int number (int /*<<< orphan*/ ) ; 
 scalar_t__ read (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
expect(char *cp)
{
	char buf[300];
	char *rp = buf;
	int timeout = 30, online = 0;

	if (strcmp(cp, "\"\"") == 0)
		return (1);
	*rp = 0;
	/*
	 * If we are waiting for the Vadic to complete
	 * dialing and get a connection, allow more time
	 * Unfortunately, the Vadic times out 24 seconds after
	 * the last digit is dialed
	 */
	online = strcmp(cp, "ON LINE") == 0;
	if (online)
		timeout = number(value(DIALTIMEOUT));
	signal(SIGALRM, alarmtr);
	if (setjmp(Sjbuf))
		return (0);
	alarm(timeout);
	while (notin(cp, buf) && rp < buf + sizeof (buf) - 1) {
		if (online && notin("FAILED CALL", buf) == 0)
			return (0);
		if (read(FD, rp, 1) < 0) {
			alarm(0);
			return (0);
		}
		if (*rp &= 0177)
			rp++;
		*rp = '\0';
	}
	alarm(0);
	return (1);
}