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
 char* malloc (int) ; 

__attribute__((used)) static char *
doublequote(char *s)
{
	int n;
	char *p, *s2;

	for (p = s, n = 0; *p; p++)
		if (*p == '"')
			n++;

	if ((s2 = malloc(p - s + n + 1)) == NULL)
		return (NULL);

	for (p = s2; *s; s++, p++) {
		if ((*p = *s) == '"')
			*(++p) = '"';
	}
	*p = '\0';

	return (s2);
}