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
 int /*<<< orphan*/  httpabort ; 
 int sigint_raised ; 
 int /*<<< orphan*/  siglongjmp (int /*<<< orphan*/ ,int) ; 
 size_t strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  ttyout ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,size_t) ; 

void
aborthttp(int notused)
{
	char msgbuf[100];
	size_t len;

	sigint_raised = 1;
	alarmtimer(0);
	len = strlcpy(msgbuf, "\nHTTP fetch aborted.\n", sizeof(msgbuf));
	write(fileno(ttyout), msgbuf, len);
	siglongjmp(httpabort, 1);
}