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
typedef  int /*<<< orphan*/  y ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  STDOUT_FILENO ; 
 scalar_t__ caph_enter () ; 
 scalar_t__ caph_limit_stdio () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int strlen (char*) ; 
 scalar_t__ write (int /*<<< orphan*/ ,char*,size_t) ; 

int
main(int argc, char **argv)
{
	char buf[8192];
	char y[2] = { 'y', '\n' };
	char * exp = y;
	size_t buflen = 0;
	size_t explen = sizeof(y);
	size_t more;
	ssize_t ret;

	if (caph_limit_stdio() < 0 || caph_enter() < 0)
		err(1, "capsicum");

	if (argc > 1) {
		exp = argv[1];
		explen = strlen(exp) + 1;
		exp[explen - 1] = '\n';
	}

	if (explen <= sizeof(buf)) {
		while (buflen < sizeof(buf) - explen) {
			memcpy(buf + buflen, exp, explen);
			buflen += explen;
		}
		exp = buf;
		explen = buflen;
	}

	more = explen;
	while ((ret = write(STDOUT_FILENO, exp + (explen - more), more)) > 0)
		if ((more -= ret) == 0)
			more = explen;

	err(1, "stdout");
	/*NOTREACHED*/
}