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
 int /*<<< orphan*/  die_bad_number (char const*,char const*) ; 
 int /*<<< orphan*/  git_parse_ulong (char const*,unsigned long*) ; 

unsigned long git_config_ulong(const char *name, const char *value)
{
	unsigned long ret;
	if (!git_parse_ulong(value, &ret))
		die_bad_number(name, value);
	return ret;
}