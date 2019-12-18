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
typedef  scalar_t__ wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  MB_LEN_MAX ; 
 int /*<<< orphan*/  errc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t mbrtowc (scalar_t__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
mbssep(char **stringp, const wchar_t *delim)
{
	char *s, *tok;
	const wchar_t *spanp;
	wchar_t c, sc;
	size_t n;

	if ((s = *stringp) == NULL)
		return (NULL);
	for (tok = s;;) {
		n = mbrtowc(&c, s, MB_LEN_MAX, NULL);
		if (n == (size_t)-1 || n == (size_t)-2)
			errc(1, EILSEQ, NULL);	/* XXX */
		s += n;
		spanp = delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == 0)
					s = NULL;
				else
					s[-n] = '\0';
				*stringp = s;
				return (tok);
			}
		} while (sc != 0);
	}
}