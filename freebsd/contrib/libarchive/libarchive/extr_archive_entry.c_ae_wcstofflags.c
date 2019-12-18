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
typedef  int wchar_t ;
struct flag {unsigned long set; unsigned long clear; int /*<<< orphan*/ * wname; } ;

/* Variables and functions */
 struct flag* flags ; 
 size_t wcslen (int /*<<< orphan*/ *) ; 
 scalar_t__ wmemcmp (int const*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static const wchar_t *
ae_wcstofflags(const wchar_t *s, unsigned long *setp, unsigned long *clrp)
{
	const wchar_t *start, *end;
	const struct flag *flag;
	unsigned long set, clear;
	const wchar_t *failed;

	set = clear = 0;
	start = s;
	failed = NULL;
	/* Find start of first token. */
	while (*start == L'\t'  ||  *start == L' '  ||  *start == L',')
		start++;
	while (*start != L'\0') {
		size_t length;
		/* Locate end of token. */
		end = start;
		while (*end != L'\0'  &&  *end != L'\t'  &&
		    *end != L' '  &&  *end != L',')
			end++;
		length = end - start;
		for (flag = flags; flag->wname != NULL; flag++) {
			size_t flag_length = wcslen(flag->wname);
			if (length == flag_length
			    && wmemcmp(start, flag->wname, length) == 0) {
				/* Matched "noXXXX", so reverse the sense. */
				clear |= flag->set;
				set |= flag->clear;
				break;
			} else if (length == flag_length - 2
			    && wmemcmp(start, flag->wname + 2, length) == 0) {
				/* Matched "XXXX", so don't reverse. */
				set |= flag->set;
				clear |= flag->clear;
				break;
			}
		}
		/* Ignore unknown flag names. */
		if (flag->wname == NULL  &&  failed == NULL)
			failed = start;

		/* Find start of next token. */
		start = end;
		while (*start == L'\t'  ||  *start == L' '  ||  *start == L',')
			start++;

	}

	if (setp)
		*setp = set;
	if (clrp)
		*clrp = clear;

	/* Return location of first failure. */
	return (failed);
}