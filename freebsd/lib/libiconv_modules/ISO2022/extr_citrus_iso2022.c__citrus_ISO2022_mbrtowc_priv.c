#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wchar_t ;
struct TYPE_5__ {int chlen; char* ch; } ;
typedef  TYPE_1__ _ISO2022State ;
typedef  int /*<<< orphan*/  _ISO2022EncodingInfo ;

/* Variables and functions */
 int EILSEQ ; 
 size_t _ENCODING_IS_STATE_DEPENDENT ; 
 scalar_t__ _ISO2022INVALID ; 
 scalar_t__ _ISO2022_sgetwchar (int /*<<< orphan*/ *,char*,size_t,char**,TYPE_1__*) ; 
 int /*<<< orphan*/  _citrus_ISO2022_init_state (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 

__attribute__((used)) static int
_citrus_ISO2022_mbrtowc_priv(_ISO2022EncodingInfo * __restrict ei,
    wchar_t * __restrict pwc, char ** __restrict s,
    size_t n, _ISO2022State * __restrict psenc, size_t * __restrict nresult)
{
	char *p, *result, *s0;
	wchar_t wchar;
	int c, chlenbak;

	if (*s == NULL) {
		_citrus_ISO2022_init_state(ei, psenc);
		*nresult = _ENCODING_IS_STATE_DEPENDENT;
		return (0);
	}
	s0 = *s;
	c = 0;
	chlenbak = psenc->chlen;

	/*
	 * if we have something in buffer, use that.
	 * otherwise, skip here
	 */
	if (psenc->chlen > sizeof(psenc->ch)) {
		/* illgeal state */
		_citrus_ISO2022_init_state(ei, psenc);
		goto encoding_error;
	}
	if (psenc->chlen == 0)
		goto emptybuf;

	/* buffer is not empty */
	p = psenc->ch;
	while (psenc->chlen < sizeof(psenc->ch)) {
		if (n > 0) {
			psenc->ch[psenc->chlen++] = *s0++;
			n--;
		}

		wchar = _ISO2022_sgetwchar(ei, p, psenc->chlen - (p-psenc->ch),
		    &result, psenc);
		c += result - p;
		if (wchar != _ISO2022INVALID) {
			if (psenc->chlen > (size_t)c)
				memmove(psenc->ch, result, psenc->chlen - c);
			if (psenc->chlen < (size_t)c)
				psenc->chlen = 0;
			else
				psenc->chlen -= c;
			goto output;
		}

		if (n == 0) {
			if ((size_t)(result - p) == psenc->chlen)
				/* complete shift sequence. */
				psenc->chlen = 0;
			goto restart;
		}

		p = result;
	}

	/* escape sequence too long? */
	goto encoding_error;

emptybuf:
	wchar = _ISO2022_sgetwchar(ei, s0, n, &result, psenc);
	if (wchar != _ISO2022INVALID) {
		c += result - s0;
		psenc->chlen = 0;
		s0 = result;
		goto output;
	}
	if (result > s0) {
		c += (result - s0);
		n -= (result - s0);
		s0 = result;
		if (n > 0)
			goto emptybuf;
		/* complete shift sequence. */
		goto restart;
	}
	n += c;
	if (n < sizeof(psenc->ch)) {
		memcpy(psenc->ch, s0 - c, n);
		psenc->chlen = n;
		s0 = result;
		goto restart;
	}

	/* escape sequence too long? */

encoding_error:
	psenc->chlen = 0;
	*nresult = (size_t)-1;
	return (EILSEQ);

output:
	*s = s0;
	if (pwc)
		*pwc = wchar;
	*nresult = wchar ? c - chlenbak : 0;
	return (0);

restart:
	*s = s0;
	*nresult = (size_t)-2;

	return (0);
}