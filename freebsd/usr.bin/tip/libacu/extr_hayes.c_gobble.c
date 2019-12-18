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
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 scalar_t__ dialtimeout ; 
 int /*<<< orphan*/  number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigALRM ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  timeoutbuf ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char
gobble(char *match)
{
	char c;
	sig_t f;
	size_t i;
	int status = 0;

	f = signal(SIGALRM, sigALRM);
	dialtimeout = 0;
#ifdef DEBUG
	printf("\ngobble: waiting for %s\n", match);
#endif
	do {
		if (setjmp(timeoutbuf)) {
			signal(SIGALRM, f);
			return (0);
		}
		alarm(number(value(DIALTIMEOUT)));
		read(FD, &c, 1);
		alarm(0);
		c &= 0177;
#ifdef DEBUG
		printf("%c 0x%x ", c, c);
#endif
		for (i = 0; i < strlen(match); i++)
			if (c == match[i])
				status = c;
	} while (status == 0);
	signal(SIGALRM, SIG_DFL);
#ifdef DEBUG
	printf("\n");
#endif
	return (status);
}