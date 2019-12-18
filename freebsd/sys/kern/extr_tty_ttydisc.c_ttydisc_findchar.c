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
 scalar_t__ CTL_VALID (char const) ; 

__attribute__((used)) static __inline unsigned int
ttydisc_findchar(const char *obstart, unsigned int oblen)
{
	const char *c = obstart;

	while (oblen--) {
		if (CTL_VALID(*c))
			break;
		c++;
	}

	return (c - obstart);
}