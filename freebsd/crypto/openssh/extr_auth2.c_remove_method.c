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
 int MATCH_BOTH ; 
 int MATCH_METHOD ; 
 int /*<<< orphan*/  free (char*) ; 
 int list_starts_with (char*,char const*,char const*) ; 
 int strlen (char const*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static int
remove_method(char **methods, const char *method, const char *submethod)
{
	char *omethods = *methods, *p;
	size_t l = strlen(method);
	int match;

	match = list_starts_with(omethods, method, submethod);
	if (match != MATCH_METHOD && match != MATCH_BOTH)
		return 0;
	p = omethods + l;
	if (submethod && match == MATCH_BOTH)
		p += 1 + strlen(submethod); /* include colon */
	if (*p == ',')
		p++;
	*methods = xstrdup(p);
	free(omethods);
	return 1;
}