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
 scalar_t__ dialtimeout ; 
 int /*<<< orphan*/  number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigALRM ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeoutbuf ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
detect(char *s)
{
	sig_t f;
	char c;

	f = signal(SIGALRM, sigALRM);
	dialtimeout = 0;
	while (*s) {
		if (setjmp(timeoutbuf)) {
			biz22_abort();
			break;
		}
		alarm(number(value(DIALTIMEOUT)));
		read(FD, &c, 1);
		alarm(0);
		c &= 0177;
		if (c != *s++)
			return (0);
	}
	signal(SIGALRM, f);
	return (dialtimeout == 0);
}