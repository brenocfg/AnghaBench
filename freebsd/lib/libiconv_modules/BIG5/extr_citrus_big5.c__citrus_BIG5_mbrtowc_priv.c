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
typedef  int /*<<< orphan*/  wint_t ;
typedef  int wchar_t ;
struct TYPE_4__ {int chlen; int* ch; } ;
typedef  TYPE_1__ _BIG5State ;
typedef  int /*<<< orphan*/  _BIG5EncodingInfo ;

/* Variables and functions */
 int EILSEQ ; 
 int _citrus_BIG5_check (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _citrus_BIG5_check2 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ _citrus_BIG5_check_excludes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _citrus_BIG5_init_state (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
/*ARGSUSED*/
_citrus_BIG5_mbrtowc_priv(_BIG5EncodingInfo * __restrict ei,
    wchar_t * __restrict pwc,
    char ** __restrict s, size_t n,
    _BIG5State * __restrict psenc,
    size_t * __restrict nresult)
{
	wchar_t wchar;
	char *s0;
	int c, chlenbak;

	s0 = *s;

	if (s0 == NULL) {
		_citrus_BIG5_init_state(ei, psenc);
		*nresult = 0;
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
		goto ilseq;
	}

	c = _citrus_BIG5_check(ei, psenc->ch[0] & 0xff);
	if (c == 0)
		goto ilseq;
	while (psenc->chlen < c) {
		if (n < 1) {
			goto restart;
		}
		psenc->ch[psenc->chlen] = *s0++;
		psenc->chlen++;
		n--;
	}

	switch (c) {
	case 1:
		wchar = psenc->ch[0] & 0xff;
		break;
	case 2:
		if (!_citrus_BIG5_check2(ei, psenc->ch[1] & 0xff))
			goto ilseq;
		wchar = ((psenc->ch[0] & 0xff) << 8) | (psenc->ch[1] & 0xff);
		break;
	default:
		/* illegal state */
		goto ilseq;
	}

	if (_citrus_BIG5_check_excludes(ei, (wint_t)wchar) != 0)
		goto ilseq;

	*s = s0;
	psenc->chlen = 0;
	if (pwc)
		*pwc = wchar;
	*nresult = wchar ? c - chlenbak : 0;

	return (0);

ilseq:
	psenc->chlen = 0;
	*nresult = (size_t)-1;
	return (EILSEQ);

restart:
	*s = s0;
	*nresult = (size_t)-2;
	return (0);
}