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
typedef  int uint8_t ;
struct TYPE_4__ {int chlen; int* ch; } ;
typedef  TYPE_1__ _UTF8State ;
typedef  int /*<<< orphan*/  _UTF8EncodingInfo ;

/* Variables and functions */
 int EILSEQ ; 
 int* _UTF8_count ; 
 int _UTF8_findlen (int) ; 
 scalar_t__ _UTF8_surrogate (int) ; 
 int /*<<< orphan*/  _citrus_UTF8_init_state (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
_citrus_UTF8_mbrtowc_priv(_UTF8EncodingInfo *ei, wchar_t *pwc, char **s,
    size_t n, _UTF8State *psenc, size_t *nresult)
{
	char *s0;
	wchar_t wchar;
	int i;
	uint8_t c;

	s0 = *s;

	if (s0 == NULL) {
		_citrus_UTF8_init_state(ei, psenc);
		*nresult = 0; /* state independent */
		return (0);
	}

	/* make sure we have the first byte in the buffer */
	if (psenc->chlen == 0) {
		if (n-- < 1)
			goto restart;
		psenc->ch[psenc->chlen++] = *s0++;
	}

	c = _UTF8_count[psenc->ch[0] & 0xff];
	if (c < 1 || c < psenc->chlen)
		goto ilseq;

	if (c == 1)
		wchar = psenc->ch[0] & 0xff;
	else {
		while (psenc->chlen < c) {
			if (n-- < 1)
				goto restart;
			psenc->ch[psenc->chlen++] = *s0++;
		}
		wchar = psenc->ch[0] & (0x7f >> c);
		for (i = 1; i < c; i++) {
			if ((psenc->ch[i] & 0xc0) != 0x80)
				goto ilseq;
			wchar <<= 6;
			wchar |= (psenc->ch[i] & 0x3f);
		}
		if (_UTF8_surrogate(wchar) || _UTF8_findlen(wchar) != c)
			goto ilseq;
	}
	if (pwc != NULL)
		*pwc = wchar;
	*nresult = (wchar == 0) ? 0 : s0 - *s;
	*s = s0;
	psenc->chlen = 0;

	return (0);

ilseq:
	*nresult = (size_t)-1;
	return (EILSEQ);

restart:
	*s = s0;
	*nresult = (size_t)-2;
	return (0);
}