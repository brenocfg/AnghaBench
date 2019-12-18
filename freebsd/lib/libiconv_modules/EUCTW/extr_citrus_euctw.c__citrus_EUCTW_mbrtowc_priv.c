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
typedef  char wchar_t ;
struct TYPE_4__ {int chlen; int* ch; } ;
typedef  TYPE_1__ _EUCTWState ;
typedef  int /*<<< orphan*/  _EUCTWEncodingInfo ;

/* Variables and functions */
 int EILSEQ ; 
 int _citrus_EUCTW_count (int) ; 
 int _citrus_EUCTW_cs (int) ; 
 int /*<<< orphan*/  _citrus_EUCTW_init_state (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
_citrus_EUCTW_mbrtowc_priv(_EUCTWEncodingInfo * __restrict ei,
    wchar_t * __restrict pwc, char ** __restrict s,
    size_t n, _EUCTWState * __restrict psenc, size_t * __restrict nresult)
{
	char *s0;
	wchar_t wchar;
	int c, chlenbak, cs;

	s0 = *s;

	if (s0 == NULL) {
		_citrus_EUCTW_init_state(ei, psenc);
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
	case 2:
		break;
	default:
		/* illgeal state */
		goto ilseq;
	}

	c = _citrus_EUCTW_count(cs = _citrus_EUCTW_cs(psenc->ch[0] & 0xff));
	if (c == 0)
		goto ilseq;
	while (psenc->chlen < c) {
		if (n < 1)
			goto ilseq;
		psenc->ch[psenc->chlen] = *s0++;
		psenc->chlen++;
		n--;
	}

	wchar = 0;
	switch (cs) {
	case 0:
		if (psenc->ch[0] & 0x80)
			goto ilseq;
		wchar = psenc->ch[0] & 0xff;
		break;
	case 1:
		if (!(psenc->ch[0] & 0x80) || !(psenc->ch[1] & 0x80))
			goto ilseq;
		wchar = ((psenc->ch[0] & 0xff) << 8) | (psenc->ch[1] & 0xff);
		wchar |= 'G' << 24;
		break;
	case 2:
		if ((unsigned char)psenc->ch[1] < 0xa1 ||
		    0xa7 < (unsigned char)psenc->ch[1])
			goto ilseq;
		if (!(psenc->ch[2] & 0x80) || !(psenc->ch[3] & 0x80))
			goto ilseq;
		wchar = ((psenc->ch[2] & 0xff) << 8) | (psenc->ch[3] & 0xff);
		wchar |= ('G' + psenc->ch[1] - 0xa1) << 24;
		break;
	default:
		goto ilseq;
	}

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
	*nresult = (size_t)-1;
	return (0);
}