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
 int atoi (char*) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ strcasecmp (char*,char const*) ; 

__attribute__((used)) static int
gettype(char *t, const char **names)
{
	const char **nm;

	for (nm = names; *nm; nm++)
		if (strcasecmp(t, *nm) == 0)
			return (nm - names);
	if (isdigit((unsigned char)*t))
		return (atoi(t));
	return (0);
}