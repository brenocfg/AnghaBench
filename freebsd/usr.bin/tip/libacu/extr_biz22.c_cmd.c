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
typedef  int /*<<< orphan*/  sig_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIALTIMEOUT ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  biz22_abort () ; 
 int /*<<< orphan*/  number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigALRM ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  timeoutbuf ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmd(char *s)
{
	sig_t f;
	char c;

	write(FD, s, strlen(s));
	f = signal(SIGALRM, sigALRM);
	if (setjmp(timeoutbuf)) {
		biz22_abort();
		signal(SIGALRM, f);
		return (1);
	}
	alarm(number(value(DIALTIMEOUT)));
	read(FD, &c, 1);
	alarm(0);
	signal(SIGALRM, f);
	c &= 0177;
	return (c != '\r');
}