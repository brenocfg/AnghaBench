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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  strtoul (char*,char**,int) ; 

__attribute__((used)) static char *parseint(char *arg, uint32_t *val, int hexonly)
{
	char *endptr = NULL;

	errno = 0;
	*val = strtoul(arg, &endptr, hexonly ? 16 : 0);
	if ((endptr && *endptr != '\0')
	    || errno != 0) {
		if (errno == ERANGE)
			return "value out of range";
		return "invalid integer input";
	}

	return NULL;
}