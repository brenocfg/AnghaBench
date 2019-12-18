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
 int EOF ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int getchar () ; 
 int /*<<< orphan*/  intprompt ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  promptbuf ; 
 int /*<<< orphan*/  raw () ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stoprompt ; 
 int /*<<< orphan*/  unraw () ; 

int
prompt(char *s, char *p, size_t sz)
{
	int c;
	char *b = p;
	sig_t oint, oquit;

	stoprompt = 0;
	oint = signal(SIGINT, intprompt);
	oquit = signal(SIGQUIT, SIG_IGN);
	unraw();
	printf("%s", s);
	if (setjmp(promptbuf) == 0)
		while ((c = getchar()) != EOF && (*p = c) != '\n' && --sz > 0)
			p++;
	*p = '\0';

	raw();
	(void)signal(SIGINT, oint);
	(void)signal(SIGQUIT, oquit);
	return (stoprompt || p == b);
}