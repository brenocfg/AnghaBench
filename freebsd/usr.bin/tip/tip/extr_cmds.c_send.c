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
 int /*<<< orphan*/  CDELAY ; 
 int /*<<< orphan*/  ECHOCHECK ; 
 int /*<<< orphan*/  ETIMEOUT ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  LDELAY ; 
 int /*<<< orphan*/  alarm (unsigned int) ; 
 int /*<<< orphan*/  boolean (int /*<<< orphan*/ ) ; 
 char* ctrl (int) ; 
 scalar_t__ lvalue (int /*<<< orphan*/ ) ; 
 char null ; 
 scalar_t__ number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parwrite (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ timedout ; 
 int /*<<< orphan*/  usleep (scalar_t__) ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
send(int c)
{
	char cc;
	int retry = 0;

	cc = c;
	parwrite(FD, &cc, 1);
	if (number(value(CDELAY)) > 0 && c != '\r')
		usleep(number(value(CDELAY)));
	if (!boolean(value(ECHOCHECK))) {
		if (number(value(LDELAY)) > 0 && c == '\r')
			usleep(number(value(LDELAY)));
		return;
	}
tryagain:
	timedout = 0;
	alarm((unsigned int)lvalue(ETIMEOUT));
	read(FD, &cc, 1);
	alarm(0);
	if (timedout) {
		printf("\r\ntimeout error (%s)\r\n", ctrl(c));
		if (retry++ > 3)
			return;
		parwrite(FD, &null, 1); /* poke it */
		goto tryagain;
	}
}