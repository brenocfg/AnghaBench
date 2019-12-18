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
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int strlen (char const*) ; 
 char* strstr (char*,char const*) ; 

__attribute__((used)) static char *
strsep(char **s, const char *del)
{
	char *d, *tok;
	EVUTIL_ASSERT(strlen(del) == 1);
	if (!s || !*s)
		return NULL;
	tok = *s;
	d = strstr(tok, del);
	if (d) {
		*d = '\0';
		*s = d + 1;
	} else
		*s = NULL;
	return tok;
}