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
typedef  int /*<<< orphan*/  msgbuf ;

/* Variables and functions */
 int /*<<< orphan*/  alarmtimer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lostpeer (int /*<<< orphan*/ ) ; 
 int sigint_raised ; 
 int /*<<< orphan*/  siglongjmp (int /*<<< orphan*/ ,int) ; 
 size_t strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  ttyout ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  xferabort ; 

void
abort_squared(int dummy)
{
	char msgbuf[100];
	size_t len;

	sigint_raised = 1;
	alarmtimer(0);
	len = strlcpy(msgbuf, "\nremote abort aborted; closing connection.\n",
	    sizeof(msgbuf));
	write(fileno(ttyout), msgbuf, len);
	lostpeer(0);
	siglongjmp(xferabort, 1);
}