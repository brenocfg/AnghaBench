#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
struct TYPE_4__ {int chlen; int* ch; } ;
typedef  TYPE_1__ _MSKanjiState ;
typedef  int /*<<< orphan*/  _MSKanjiEncodingInfo ;

/* Variables and functions */
 int EILSEQ ; 
 int /*<<< orphan*/  _citrus_MSKanji_init_state (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ _mskanji1 (int) ; 
 int /*<<< orphan*/  _mskanji2 (int) ; 

__attribute__((used)) static int
/*ARGSUSED*/
_citrus_MSKanji_mbrtowc_priv(_MSKanjiEncodingInfo * __restrict ei,
    wchar_t * __restrict pwc, char ** __restrict s, size_t n,
    _MSKanjiState * __restrict psenc, size_t * __restrict nresult)
{
	char *s0;
	wchar_t wchar;
	int chlenbak, len;

	s0 = *s;

	if (s0 == NULL) {
		_citrus_MSKanji_init_state(ei, psenc);
		*nresult = 0; /* state independent */
		return (0);
	}

	chlenbak = psenc->chlen;

	/* make sure we have the first byte in the buffer */
	switch (psenc->chlen) {
	case 0:
		if (n < 1)
			goto restart;
		psenc->ch[0] = *s0++;
		psenc->chlen = 1;
		n--;
		break;
	case 1:
		break;
	default:
		/* illegal state */
		goto encoding_error;
	}

	len = _mskanji1(psenc->ch[0] & 0xff) ? 2 : 1;
	while (psenc->chlen < len) {
		if (n < 1)
			goto restart;
		psenc->ch[psenc->chlen] = *s0++;
		psenc->chlen++;
		n--;
	}

	*s = s0;

	switch (len) {
	case 1:
		wchar = psenc->ch[0] & 0xff;
		break;
	case 2:
		if (!_mskanji2(psenc->ch[1] & 0xff))
			goto encoding_error;
		wchar = ((psenc->ch[0] & 0xff) << 8) | (psenc->ch[1] & 0xff);
		break;
	default:
		/* illegal state */
		goto encoding_error;
	}

	psenc->chlen = 0;

	if (pwc)
		*pwc = wchar;
	*nresult = wchar ? len - chlenbak : 0;
	return (0);

encoding_error:
	psenc->chlen = 0;
	*nresult = (size_t)-1;
	return (EILSEQ);

restart:
	*nresult = (size_t)-2;
	*s = s0;
	return (0);
}