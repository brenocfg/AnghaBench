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
width(register char *s, register char *os)
{
	register int i = 0;

	while (s < os) {
		if (*s == '\t') {
			i = (i + 8) &~ 7;
			s++;
			continue;
		}
		if (*s < ' ')
			i += 2;
		else
			i++;
		s++;
	}
	return (i);
}