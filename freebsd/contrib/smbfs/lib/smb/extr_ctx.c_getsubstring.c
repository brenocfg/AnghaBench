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
typedef  char const u_char ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
getsubstring(const char *p, u_char sep, char *dest, int maxlen, const char **next)
{
	int len;

	maxlen--;
	for (len = 0; len < maxlen && *p != sep; p++, len++, dest++) {
		if (*p == 0)
			return EINVAL;
		*dest = *p;
	}
	*dest = 0;
	*next = *p ? p + 1 : p;
	return 0;
}