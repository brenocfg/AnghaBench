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
typedef  scalar_t__ u_int ;

/* Variables and functions */

__attribute__((used)) static bool
mem_iszero(void *dat, int len)
{
	int i;
	const u_int *p;
	const char *cp;

	for (p = dat; len > 0; len -= sizeof(*p), p++) {
		if (len >= sizeof(*p)) {
			if (*p != 0)
				return (false);
		} else {
			cp = (const char *)p;
			for (i = 0; i < len; i++, cp++)
				if (*cp != '\0')
					return (false);
		}
	}
	return (true);
}