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
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static int
boolstr_to_bool(const char *str)
{
	if (str != NULL && (strcasecmp(str, "true") == 0 ||
	    strcasecmp(str, "yes") == 0 || strcasecmp(str, "on") == 0 ||
	    str[0] == '1'))
		return (true);

	return (false);
}