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
 char* calloc (int,size_t) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncat (char*,char*,uintptr_t) ; 
 char* strstr (char*,char const*) ; 

void
strnsubst(char **str, const char *match, const char *replstr, size_t maxsize)
{
	char *s1, *s2, *this;

	s1 = *str;
	if (s1 == NULL)
		return;
	/*
	 * If maxsize is 0 then set it to the length of s1, because we have
	 * to duplicate s1.  XXX we maybe should double-check whether the match
	 * appears in s1.  If it doesn't, then we also have to set the length
	 * to the length of s1, to avoid modifying the argument.  It may make
	 * sense to check if maxsize is <= strlen(s1), because in that case we
	 * want to return the unmodified string, too.
	 */
	if (maxsize == 0) {
		match = NULL;
		maxsize = strlen(s1) + 1;
	}
	s2 = calloc(1, maxsize);
	if (s2 == NULL)
		err(1, "calloc");

	if (replstr == NULL)
		replstr = "";

	if (match == NULL || replstr == NULL || maxsize == strlen(s1)) {
		strlcpy(s2, s1, maxsize);
		goto done;
	}

	for (;;) {
		this = strstr(s1, match);
		if (this == NULL)
			break;
		if ((strlen(s2) + strlen(s1) + strlen(replstr) -
		    strlen(match) + 1) > maxsize) {
			strlcat(s2, s1, maxsize);
			goto done;
		}
		strncat(s2, s1, (uintptr_t)this - (uintptr_t)s1);
		strcat(s2, replstr);
		s1 = this + strlen(match);
	}
	strcat(s2, s1);
done:
	*str = s2;
	return;
}