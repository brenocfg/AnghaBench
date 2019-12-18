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
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 scalar_t__ dialtimeout ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigALRM ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  timeoutbuf ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
t3000_swallow(char *match)
{
	sig_t f;
	char c;

	f = signal(SIGALRM, sigALRM);
	dialtimeout = 0;
	do {
		if (*match =='\0') {
			signal(SIGALRM, f);
			return (1);
		}
		if (setjmp(timeoutbuf)) {
			signal(SIGALRM, f);
			return (0);
		}
		alarm(number(value(DIALTIMEOUT)));
		read(FD, &c, 1);
		alarm(0);
		c &= 0177;
#ifdef DEBUG
		if (boolean(value(VERBOSE)))
			putchar(c);
#endif
	} while (c == *match++);
#ifdef DEBUG
	if (boolean(value(VERBOSE)))
		fflush(stdout);
#endif
	signal(SIGALRM, SIG_DFL);
	return (0);
}