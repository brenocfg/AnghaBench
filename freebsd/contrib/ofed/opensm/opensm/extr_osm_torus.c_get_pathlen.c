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

__attribute__((used)) static
void get_pathlen(unsigned src, unsigned dst, unsigned count,
		 unsigned *vl0_len, unsigned *vl1_len)
{
	unsigned s, l;		/* assume s < l */

	if (dst > src) {
		s = src;
		l = dst;
	} else {
		s = dst;
		l = src;
	}
	*vl0_len = l - s;
	*vl1_len = s + count - l;
}