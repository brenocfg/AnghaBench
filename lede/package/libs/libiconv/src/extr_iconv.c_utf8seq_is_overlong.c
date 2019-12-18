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

__attribute__((used)) static inline int utf8seq_is_overlong(char *s, int n)
{
	switch (n)
	{
	case 2:
		/* 1100000x (10xxxxxx) */
		return (((*s >> 1) == 0x60) &&
				((*(s+1) >> 6) == 0x02));

	case 3:
		/* 11100000 100xxxxx (10xxxxxx) */
		return ((*s == 0xE0) &&
				((*(s+1) >> 5) == 0x04) &&
				((*(s+2) >> 6) == 0x02));

	case 4:
		/* 11110000 1000xxxx (10xxxxxx 10xxxxxx) */
		return ((*s == 0xF0) &&
				((*(s+1) >> 4) == 0x08) &&
				((*(s+2) >> 6) == 0x02) &&
				((*(s+3) >> 6) == 0x02));
	}

	return 0;
}