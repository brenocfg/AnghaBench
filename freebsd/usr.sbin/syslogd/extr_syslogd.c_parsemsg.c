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
 int DEFUPRI ; 
 long INT_MAX ; 
 int /*<<< orphan*/  KeepKernFac ; 
 int LOG_FACMASK ; 
 int LOG_KERN ; 
 int LOG_MAKEPRI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_PRI (int) ; 
 int LOG_PRIMASK ; 
 int /*<<< orphan*/  LOG_USER ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/  parsemsg_rfc3164 (char const*,int,char*) ; 
 int /*<<< orphan*/  parsemsg_rfc5424 (char const*,int,char*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static void
parsemsg(const char *from, char *msg)
{
	char *q;
	long n;
	size_t i;
	int pri;

	/* Parse PRI. */
	if (msg[0] != '<' || !isdigit(msg[1])) {
		dprintf("Invalid PRI from %s\n", from);
		return;
	}
	for (i = 2; i <= 4; i++) {
		if (msg[i] == '>')
			break;
		if (!isdigit(msg[i])) {
			dprintf("Invalid PRI header from %s\n", from);
			return;
		}
	}
	if (msg[i] != '>') {
		dprintf("Invalid PRI header from %s\n", from);
		return;
	}
	errno = 0;
	n = strtol(msg + 1, &q, 10);
	if (errno != 0 || *q != msg[i] || n < 0 || n >= INT_MAX) {
		dprintf("Invalid PRI %ld from %s: %s\n",
		    n, from, strerror(errno));
		return;
	}
	pri = n;
	if (pri &~ (LOG_FACMASK|LOG_PRIMASK))
		pri = DEFUPRI;

	/*
	 * Don't allow users to log kernel messages.
	 * NOTE: since LOG_KERN == 0 this will also match
	 *       messages with no facility specified.
	 */
	if ((pri & LOG_FACMASK) == LOG_KERN && !KeepKernFac)
		pri = LOG_MAKEPRI(LOG_USER, LOG_PRI(pri));

	/* Parse VERSION. */
	msg += i + 1;
	if (msg[0] == '1' && msg[1] == ' ')
		parsemsg_rfc5424(from, pri, msg + 2);
	else
		parsemsg_rfc3164(from, pri, msg);
}