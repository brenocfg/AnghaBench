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
 unsigned int PATTERN_FLAG_ENDSWITH ; 
 unsigned int PATTERN_FLAG_MUSTBEDIR ; 
 unsigned int PATTERN_FLAG_NEGATIVE ; 
 unsigned int PATTERN_FLAG_NODIR ; 
 scalar_t__ no_wildcard (char const*) ; 
 int simple_length (char const*) ; 
 size_t strlen (char const*) ; 

void parse_path_pattern(const char **pattern,
			   int *patternlen,
			   unsigned *flags,
			   int *nowildcardlen)
{
	const char *p = *pattern;
	size_t i, len;

	*flags = 0;
	if (*p == '!') {
		*flags |= PATTERN_FLAG_NEGATIVE;
		p++;
	}
	len = strlen(p);
	if (len && p[len - 1] == '/') {
		len--;
		*flags |= PATTERN_FLAG_MUSTBEDIR;
	}
	for (i = 0; i < len; i++) {
		if (p[i] == '/')
			break;
	}
	if (i == len)
		*flags |= PATTERN_FLAG_NODIR;
	*nowildcardlen = simple_length(p);
	/*
	 * we should have excluded the trailing slash from 'p' too,
	 * but that's one more allocation. Instead just make sure
	 * nowildcardlen does not exceed real patternlen
	 */
	if (*nowildcardlen > len)
		*nowildcardlen = len;
	if (*p == '*' && no_wildcard(p + 1))
		*flags |= PATTERN_FLAG_ENDSWITH;
	*pattern = p;
	*patternlen = len;
}