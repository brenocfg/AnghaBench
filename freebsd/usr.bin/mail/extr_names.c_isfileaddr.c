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

int
isfileaddr(char *name)
{
	char *cp;

	if (*name == '+')
		return (1);
	for (cp = name; *cp != '\0'; cp++) {
		if (*cp == '!' || *cp == '%' || *cp == '@')
			return (0);
		if (*cp == '/')
			return (1);
	}
	return (0);
}