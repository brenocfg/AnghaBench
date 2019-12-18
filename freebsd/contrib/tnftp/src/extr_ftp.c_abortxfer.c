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
 scalar_t__ abrtflag ; 
 int /*<<< orphan*/  alarmtimer (int /*<<< orphan*/ ) ; 
 int* direction ; 
 int /*<<< orphan*/  errx (int,char*,int*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ mflag ; 
 int sigint_raised ; 
 int /*<<< orphan*/  siglongjmp (int /*<<< orphan*/ ,int) ; 
 size_t strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  ttyout ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  xferabort ; 

void
abortxfer(int notused)
{
	char msgbuf[100];
	size_t len;

	sigint_raised = 1;
	alarmtimer(0);
	mflag = 0;
	abrtflag = 0;
	switch (direction[0]) {
	case 'r':
		strlcpy(msgbuf, "\nreceive", sizeof(msgbuf));
		break;
	case 's':
		strlcpy(msgbuf, "\nsend", sizeof(msgbuf));
		break;
	default:
		errx(1, "abortxfer: unknown direction `%s'", direction);
	}
	len = strlcat(msgbuf, " aborted. Waiting for remote to finish abort.\n",
	    sizeof(msgbuf));
	write(fileno(ttyout), msgbuf, len);
	siglongjmp(xferabort, 1);
}