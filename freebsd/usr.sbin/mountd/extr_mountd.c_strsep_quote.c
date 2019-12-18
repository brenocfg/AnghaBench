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
 scalar_t__ strchr (char const*,char) ; 

__attribute__((used)) static char *
strsep_quote(char **stringp, const char *delim)
{
	char *srcptr, *dstptr, *retval;
	char quot = 0;
	
	if (stringp == NULL || *stringp == NULL)
		return (NULL);

	srcptr = dstptr = retval = *stringp;

	while (*srcptr) {
		/*
		 * We're looking for several edge cases here.
		 * First:  if we're in quote state (quot != 0),
		 * then we ignore the delim characters, but otherwise
		 * process as normal, unless it is the quote character.
		 * Second:  if the current character is a backslash,
		 * we take the next character as-is, without checking
		 * for delim, quote, or backslash.  Exception:  if the
		 * next character is a NUL, that's the end of the string.
		 * Third:  if the character is a quote character, we toggle
		 * quote state.
		 * Otherwise:  check the current character for NUL, or
		 * being in delim, and end the string if either is true.
		 */
		if (*srcptr == '\\') {
			srcptr++;
			/*
			 * The edge case here is if the next character
			 * is NUL, we want to stop processing.  But if
			 * it's not NUL, then we simply want to copy it.
			 */
			if (*srcptr) {
				*dstptr++ = *srcptr++;
			}
			continue;
		}
		if (quot == 0 && (*srcptr == '\'' || *srcptr == '"')) {
			quot = *srcptr++;
			continue;
		}
		if (quot && *srcptr == quot) {
			/* End of the quoted part */
			quot = 0;
			srcptr++;
			continue;
		}
		if (!quot && strchr(delim, *srcptr))
			break;
		*dstptr++ = *srcptr++;
	}

	*stringp = (*srcptr == '\0') ? NULL : srcptr + 1;
	*dstptr = 0; /* Terminate the string */
	return (retval);
}