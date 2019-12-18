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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 int MB_LEN_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 size_t wcrtomb (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t wcsrtombs (char*,int /*<<< orphan*/  const**,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
__wcsconv(wchar_t *wcsarg, int prec)
{
	static const mbstate_t initial;
	mbstate_t mbs;
	char buf[MB_LEN_MAX];
	wchar_t *p;
	char *convbuf;
	size_t clen, nbytes;

	/* Allocate space for the maximum number of bytes we could output. */
	if (prec < 0) {
		p = wcsarg;
		mbs = initial;
		nbytes = wcsrtombs(NULL, (const wchar_t **)&p, 0, &mbs);
		if (nbytes == (size_t)-1)
			return (NULL);
	} else {
		/*
		 * Optimisation: if the output precision is small enough,
		 * just allocate enough memory for the maximum instead of
		 * scanning the string.
		 */
		if (prec < 128)
			nbytes = prec;
		else {
			nbytes = 0;
			p = wcsarg;
			mbs = initial;
			for (;;) {
				clen = wcrtomb(buf, *p++, &mbs);
				if (clen == 0 || clen == (size_t)-1 ||
				    (int)(nbytes + clen) > prec)
					break;
				nbytes += clen;
			}
		}
	}
	if ((convbuf = malloc(nbytes + 1)) == NULL)
		return (NULL);

	/* Fill the output buffer. */
	p = wcsarg;
	mbs = initial;
	if ((nbytes = wcsrtombs(convbuf, (const wchar_t **)&p,
	    nbytes, &mbs)) == (size_t)-1) {
		free(convbuf);
		return (NULL);
	}
	convbuf[nbytes] = '\0';
	return (convbuf);
}