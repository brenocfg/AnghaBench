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
 char* ignore_pats ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int strlen (char*) ; 
 char* xreallocarray (char*,int,size_t) ; 
 char* xstrdup (char*) ; 

void
push_ignore_pats(char *pattern)
{
	size_t len;

	if (ignore_pats == NULL)
		ignore_pats = xstrdup(pattern);
	else {
		/* old + "|" + new + NUL */
		len = strlen(ignore_pats) + strlen(pattern) + 2;
		ignore_pats = xreallocarray(ignore_pats, 1, len);
		strlcat(ignore_pats, "|", len);
		strlcat(ignore_pats, pattern, len);
	}
}