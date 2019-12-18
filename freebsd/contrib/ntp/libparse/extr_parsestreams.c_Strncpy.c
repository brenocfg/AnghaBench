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

__attribute__((used)) static void
Strncpy(
	register char *t,
	register char *s,
	register int   c
	)
{
	if (s && t)
	{
		while ((c-- > 0) && (*t++ = *s++))
		    ;
	}
}