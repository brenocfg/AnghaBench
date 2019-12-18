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
 scalar_t__ strchr (char const*,char const) ; 

__attribute__((used)) static size_t strcspn_escaped(const char *s, const char *stop)
{
	const char *i;

	for (i = s; *i; i++) {
		/* skip the escaped character */
		if (i[0] == '\\' && i[1]) {
			i++;
			continue;
		}

		if (strchr(stop, *i))
			break;
	}
	return i - s;
}