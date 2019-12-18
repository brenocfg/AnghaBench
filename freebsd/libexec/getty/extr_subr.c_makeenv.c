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
typedef  int /*<<< orphan*/  termbuf ;

/* Variables and functions */
 char* EV ; 
 scalar_t__* TT ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcat (char*,scalar_t__*,int) ; 

void
makeenv(char *env[])
{
	static char termbuf[128] = "TERM=";
	char *p, *q;
	char **ep;

	ep = env;
	if (TT && *TT) {
		strlcat(termbuf, TT, sizeof(termbuf));
		*ep++ = termbuf;
	}
	if ((p = EV)) {
		q = p;
		while ((q = strchr(q, ','))) {
			*q++ = '\0';
			*ep++ = p;
			p = q;
		}
		if (*p)
			*ep++ = p;
	}
	*ep = (char *)0;
}