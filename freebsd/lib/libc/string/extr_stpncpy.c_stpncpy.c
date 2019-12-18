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

char *
stpncpy(char * __restrict dst, const char * __restrict src, size_t n)
{

	for (; n--; dst++, src++) {
		if (!(*dst = *src)) {
			char *ret = dst;
			while (n--)
				*++dst = '\0';
			return (ret);
		}
	}
	return (dst);
}