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
struct fixs {scalar_t__ len; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 struct fixs* nsequences ; 
 int /*<<< orphan*/ * sequences ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static int
indextooffset(char *s)
{
	int i;
	struct fixs *n;
	char *es;

	if (s[0] == '+' || s[0] == '-') {
		i = strtol (s, &es, 10);
		if (*es != '\0')                      /* trailing junk */
			errx (1, "Invalid specifier format: %s\n", s);
		return (i);
	}

	for (i = 0; i < 6; i++) {
		if (strcasecmp(s, sequences[i]) == 0) {
			if (i == 5)
				return (-1);
			return (i + 1);
		}
	}
	for (i = 0; i < 6; i++) {
		n = nsequences + i;
		if (n->len == 0)
			continue;
		if (strncasecmp(s, n->name, n->len) == 0) {
			if (i == 5)
				return (-1);
			return (i + 1);
		}
	}
	return (0);
}