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
typedef  int u_int ;

/* Variables and functions */
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static u_int
extract_strings(const char *strings, const char **dest, u_int len)
{
	u_int num;
	const char *p;

	for (p = strings, num = 0; p < strings + len; p += strlen(p) + 1) {
		if (dest != NULL)
			*dest++ = p;
		num++;
	}

	return (num);
}