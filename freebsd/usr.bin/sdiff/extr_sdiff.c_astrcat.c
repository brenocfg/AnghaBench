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
 int /*<<< orphan*/  err (int,char*) ; 
 char* realloc (char*,size_t) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
astrcat(char **s, const char *append)
{
	/* Length of string in previous run. */
	static size_t offset = 0;
	size_t newsiz;
	/*
	 * String from previous run.  Compared to *s to see if we are
	 * dealing with the same string.  If so, we can use offset.
	 */
	static const char *oldstr = NULL;
	char *newstr;

	/*
	 * First string is NULL, so just copy append.
	 */
	if (!*s) {
		if (!(*s = strdup(append)))
			err(2, "astrcat");

		/* Keep track of string. */
		offset = strlen(*s);
		oldstr = *s;

		return;
	}

	/*
	 * *s is a string so concatenate.
	 */

	/* Did we process the same string in the last run? */
	/*
	 * If this is a different string from the one we just processed
	 * cache new string.
	 */
	if (oldstr != *s) {
		offset = strlen(*s);
		oldstr = *s;
	}

	/* Size = strlen(*s) + \n + strlen(append) + '\0'. */
	newsiz = offset + 1 + strlen(append) + 1;

	/* Resize *s to fit new string. */
	newstr = realloc(*s, newsiz);
	if (newstr == NULL)
		err(2, "astrcat");
	*s = newstr;

	/* *s + offset should be end of string. */
	/* Concatenate. */
	strlcpy(*s + offset, "\n", newsiz - offset);
	strlcat(*s + offset, append, newsiz - offset);

	/* New string length should be exactly newsiz - 1 characters. */
	/* Store generated string's values. */
	offset = newsiz - 1;
	oldstr = *s;
}