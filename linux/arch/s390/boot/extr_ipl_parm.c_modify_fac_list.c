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
 int /*<<< orphan*/  check_cleared_facilities () ; 
 int /*<<< orphan*/  modify_facility (unsigned long,int) ; 
 unsigned long simple_strtoull (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void modify_fac_list(char *str)
{
	unsigned long val, endval;
	char *endp;
	bool clear;

	while (*str) {
		clear = false;
		if (*str == '!') {
			clear = true;
			str++;
		}
		val = simple_strtoull(str, &endp, 0);
		if (str == endp)
			break;
		str = endp;
		if (*str == '-') {
			str++;
			endval = simple_strtoull(str, &endp, 0);
			if (str == endp)
				break;
			str = endp;
			while (val <= endval) {
				modify_facility(val, clear);
				val++;
			}
		} else {
			modify_facility(val, clear);
		}
		if (*str != ',')
			break;
		str++;
	}
	check_cleared_facilities();
}