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
 int strcmp (char const*,char const*) ; 

int strcmp_offset(const char *s1, const char *s2, size_t *first_change)
{
	size_t k;

	if (!first_change)
		return strcmp(s1, s2);

	for (k = 0; s1[k] == s2[k]; k++)
		if (s1[k] == '\0')
			break;

	*first_change = k;
	return (unsigned char)s1[k] - (unsigned char)s2[k];
}