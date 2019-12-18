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
 int strtol (char const*,char**,int) ; 

__attribute__((used)) static int
get_number(const char *str, int low, int max)
{

	char *end = NULL;
	int res = 0;

	if (str[0] == '\0')
		return (-1);

	res = strtol(str, &end, 10);
	if (*end != '\0')
		return (-1);
	else
		if (((res >= low) || (low == -1)) &&
			((res <= max) || (max == -1)))
			return (res);
		else
			return (-2);
}