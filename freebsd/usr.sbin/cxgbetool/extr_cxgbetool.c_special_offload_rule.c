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
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int
special_offload_rule(char *str)
{

	/* skip leading whitespaces */
	while (isspace(*str))
		str++;

	/* check for special strings: "-", "all", "any" */
	if (*str == '-') {
		str++;
	} else if (!strncmp(str, "all", 3) || !strncmp(str, "any", 3)) {
		str += 3;
	} else {
		return (0);
	}

	/* skip trailing whitespaces */
	while (isspace(*str))
		str++;

	return (*str == '\0');
}