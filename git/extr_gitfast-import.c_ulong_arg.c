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
 int /*<<< orphan*/  die (char*,char const*) ; 
 scalar_t__ strchr (char const*,char) ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long ulong_arg(const char *option, const char *arg)
{
	char *endptr;
	unsigned long rv = strtoul(arg, &endptr, 0);
	if (strchr(arg, '-') || endptr == arg || *endptr)
		die("%s: argument must be a non-negative integer", option);
	return rv;
}