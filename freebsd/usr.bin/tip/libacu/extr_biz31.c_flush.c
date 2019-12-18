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
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigALRM ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ timeout ; 
 int /*<<< orphan*/  timeoutbuf ; 

__attribute__((used)) static int
flush(char *s)
{
	sig_t f;
	char c;

	f = signal(SIGALRM, sigALRM);
	while (*s++) {
		if (setjmp(timeoutbuf))
			break;
		alarm(10);
		read(FD, &c, 1);
		alarm(0);
	}
	signal(SIGALRM, f);
	timeout = 0;			/* guard against disconnection */
}