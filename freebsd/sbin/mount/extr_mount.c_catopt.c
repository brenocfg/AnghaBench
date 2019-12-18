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
 int asprintf (char**,char*,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 

char *
catopt(char *s0, const char *s1)
{
	char *cp;

	if (s1 == NULL || *s1 == '\0')
		return (s0);

	if (s0 && *s0) {
		if (asprintf(&cp, "%s,%s", s0, s1) == -1)
			errx(1, "asprintf failed");
	} else
		cp = strdup(s1);

	if (s0)
		free(s0);
	return (cp);
}