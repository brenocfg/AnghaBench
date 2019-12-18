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
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  MB_CUR_MAX ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  initial_mbs ; 
 int* malloc (size_t) ; 
 size_t mbrlen (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t mbrtowc (int*,char const*,size_t,int /*<<< orphan*/ *) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static wchar_t *
__mbsconv(char *mbsarg, int prec)
{
	mbstate_t mbs;
	wchar_t *convbuf, *wcp;
	const char *p;
	size_t insize, nchars, nconv;

	if (mbsarg == NULL)
		return (NULL);

	/*
	 * Supplied argument is a multibyte string; convert it to wide
	 * characters first.
	 */
	if (prec >= 0) {
		/*
		 * String is not guaranteed to be NUL-terminated. Find the
		 * number of characters to print.
		 */
		p = mbsarg;
		insize = nchars = nconv = 0;
		mbs = initial_mbs;
		while (nchars != (size_t)prec) {
			nconv = mbrlen(p, MB_CUR_MAX, &mbs);
			if (nconv == 0 || nconv == (size_t)-1 ||
			    nconv == (size_t)-2)
				break;
			p += nconv;
			nchars++;
			insize += nconv;
		}
		if (nconv == (size_t)-1 || nconv == (size_t)-2)
			return (NULL);
	} else {
		insize = strlen(mbsarg);
		nconv = 0;
	}

	/*
	 * Allocate buffer for the result and perform the conversion,
	 * converting at most `size' bytes of the input multibyte string to
	 * wide characters for printing.
	 */
	convbuf = malloc((insize + 1) * sizeof(*convbuf));
	if (convbuf == NULL)
		return (NULL);
	wcp = convbuf;
	p = mbsarg;
	mbs = initial_mbs;
	while (insize != 0) {
		nconv = mbrtowc(wcp, p, insize, &mbs);
		if (nconv == 0 || nconv == (size_t)-1 || nconv == (size_t)-2)
			break;
		wcp++;
		p += nconv;
		insize -= nconv;
	}
	if (nconv == (size_t)-1 || nconv == (size_t)-2) {
		free(convbuf);
		return (NULL);
	}
	*wcp = L'\0';

	return (convbuf);
}