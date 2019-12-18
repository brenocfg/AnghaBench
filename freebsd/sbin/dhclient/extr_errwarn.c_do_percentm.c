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

/* Variables and functions */
 int errno ; 
 size_t snprintf (char*,size_t,char*,char*) ; 
 char* strerror (int) ; 

__attribute__((used)) static void
do_percentm(char *obuf, size_t size, const char *ibuf)
{
	char ch;
	const char *s = ibuf;
	char *t = obuf;
	size_t prlen;
	size_t fmt_left;
	int saved_errno = errno;

	/*
	 * We wouldn't need this mess if printf handled %m, or if
	 * strerror() had been invented before syslog().
	 */
	for (fmt_left = size; (ch = *s); ++s) {
		if (ch == '%' && s[1] == 'm') {
			++s;
			prlen = snprintf(t, fmt_left, "%s",
			    strerror(saved_errno));
			if (prlen >= fmt_left)
				prlen = fmt_left - 1;
			t += prlen;
			fmt_left -= prlen;
		} else {
			if (fmt_left > 1) {
				*t++ = ch;
				fmt_left--;
			}
		}
	}
	*t = '\0';
}