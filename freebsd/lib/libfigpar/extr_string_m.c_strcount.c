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
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

unsigned int
strcount(const char *source, const char *find)
{
	const char *p = source;
	size_t flen;
	unsigned int n = 0;

	/* Both parameters are required */
	if (source == NULL || find == NULL)
		return (0);

	/* Cache the length of find element */
	flen = strlen(find);
	if (strlen(source) == 0 || flen == 0)
		return (0);

	/* Loop until the end of the string */
	while (*p != '\0') {
		if (strncmp(p, find, flen) == 0) { /* found an instance */
			p += flen;
			n++;
		} else
			p++;
	}

	return (n);
}