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
 int sprintf (char*,char*,char*,char const*) ; 

__attribute__((used)) static inline int
print_flag (const char *flag, bool *need_or, char *val)
{
	int res;
	res = sprintf (val, "%s%s", *need_or ? "|" : "", flag);

	*need_or |= true;

	return res;
}