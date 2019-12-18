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
 char* emalloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 
 int /*<<< orphan*/  special_chars ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 size_t strcspn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 size_t strlen (char*) ; 

char *
quote_if_needed(char *str)
{
	char *ret;
	size_t len;
	size_t octets;

	len = strlen(str);
	octets = len + 2 + 1;
	ret = emalloc(octets);
	if ('"' != str[0] 
	    && (strcspn(str, special_chars) < len 
		|| strchr(str, ' ') != NULL)) {
		snprintf(ret, octets, "\"%s\"", str);
	} else
		strlcpy(ret, str, octets);

	return ret;
}