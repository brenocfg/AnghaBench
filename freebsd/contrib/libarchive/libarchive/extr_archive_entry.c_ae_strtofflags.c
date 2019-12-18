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
struct flag {unsigned long set; unsigned long clear; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 struct flag* flags ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ *,size_t) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
ae_strtofflags(const char *s, unsigned long *setp, unsigned long *clrp)
{
	const char *start, *end;
	const struct flag *flag;
	unsigned long set, clear;
	const char *failed;

	set = clear = 0;
	start = s;
	failed = NULL;
	/* Find start of first token. */
	while (*start == '\t'  ||  *start == ' '  ||  *start == ',')
		start++;
	while (*start != '\0') {
		size_t length;
		/* Locate end of token. */
		end = start;
		while (*end != '\0'  &&  *end != '\t'  &&
		    *end != ' '  &&  *end != ',')
			end++;
		length = end - start;
		for (flag = flags; flag->name != NULL; flag++) {
			size_t flag_length = strlen(flag->name);
			if (length == flag_length
			    && memcmp(start, flag->name, length) == 0) {
				/* Matched "noXXXX", so reverse the sense. */
				clear |= flag->set;
				set |= flag->clear;
				break;
			} else if (length == flag_length - 2
			    && memcmp(start, flag->name + 2, length) == 0) {
				/* Matched "XXXX", so don't reverse. */
				set |= flag->set;
				clear |= flag->clear;
				break;
			}
		}
		/* Ignore unknown flag names. */
		if (flag->name == NULL  &&  failed == NULL)
			failed = start;

		/* Find start of next token. */
		start = end;
		while (*start == '\t'  ||  *start == ' '  ||  *start == ',')
			start++;

	}

	if (setp)
		*setp = set;
	if (clrp)
		*clrp = clear;

	/* Return location of first failure. */
	return (failed);
}