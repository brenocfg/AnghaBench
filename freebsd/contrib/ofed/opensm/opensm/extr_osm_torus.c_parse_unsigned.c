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
 char* strtok (int /*<<< orphan*/ *,char const*) ; 
 unsigned int strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
bool parse_unsigned(unsigned *result, const char *parse_sep)
{
	char *val, *nextchar;

	val = strtok(NULL, parse_sep);
	if (!val)
		return false;
	*result = strtoul(val, &nextchar, 0);
	return true;
}