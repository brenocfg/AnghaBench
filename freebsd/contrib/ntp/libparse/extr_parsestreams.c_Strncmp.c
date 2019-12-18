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

__attribute__((used)) static int
Strncmp(
	register char *s,
	register char *t,
	register int n
	)
{
	register int c = 0;

	if (!s || !t || (s == t))
	{
		return 0;
	}

	while (n-- && !(c = *s++ - *t++) && *s && *t)
	    /* empty loop */;

	return c;
}