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

/* Variables and functions */

wchar_t *
wcstok(wchar_t * __restrict s, const wchar_t * __restrict delim,
    wchar_t ** __restrict last)
{
	const wchar_t *spanp;
	wchar_t *tok;
	wchar_t c, sc;

	if (s == NULL && (s = *last) == NULL)
		return (NULL);

	/*
	 * Skip (span) leading delimiters (s += wcsspn(s, delim), sort of).
	 */
cont:
	c = *s++;
	for (spanp = delim; (sc = *spanp++) != L'\0';) {
		if (c == sc)
			goto cont;
	}

	if (c == L'\0') {	/* no non-delimiter characters */
		*last = NULL;
		return (NULL);
	}
	tok = s - 1;

	/*
	 * Scan token (scan for delimiters: s += wcscspn(s, delim), sort of).
	 * Note that delim must have one NUL; we stop if we see that, too.
	 */
	for (;;) {
		c = *s++;
		spanp = delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == L'\0')
					s = NULL;
				else
					s[-1] = L'\0';
				*last = s;
				return (tok);
			}
		} while (sc != L'\0');
	}
	/* NOTREACHED */
}