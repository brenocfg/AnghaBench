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

__attribute__((used)) static int strequal_ignore_eol(const char *exp, const char *str)
{
	while (*exp && *str) {
		if (*exp != *str) {
			while (*exp == '\r' || *exp == '\n') ++exp;
			while (*str == '\r' || *str == '\n') ++str;
			if (*exp != *str)
				return false;
		} else {
			exp++; str++;
		}
	}
	return (!*exp && !*str);
}