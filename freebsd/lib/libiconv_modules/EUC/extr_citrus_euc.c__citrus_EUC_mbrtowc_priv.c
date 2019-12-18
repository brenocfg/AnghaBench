#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
struct TYPE_7__ {int chlen; int* ch; } ;
typedef  TYPE_1__ _EUCState ;
struct TYPE_8__ {int* count; int mask; int* bits; } ;
typedef  TYPE_2__ _EUCEncodingInfo ;

/* Variables and functions */
 int EILSEQ ; 
 int _citrus_EUC_cs (int) ; 
 int /*<<< orphan*/  _citrus_EUC_init_state (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static int
_citrus_EUC_mbrtowc_priv(_EUCEncodingInfo *ei, wchar_t *pwc, char **s,
    size_t n, _EUCState *psenc, size_t *nresult)
{
	wchar_t wchar;
	int c, chlenbak, cs, len;
	char *s0, *s1 = NULL;

	s0 = *s;

	if (s0 == NULL) {
		_citrus_EUC_init_state(ei, psenc);
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
		goto encoding_error;
	}

	c = ei->count[cs = _citrus_EUC_cs(psenc->ch[0] & 0xff)];
	if (c == 0)
		goto encoding_error;
	while (psenc->chlen < c) {
		if (n < 1)
			goto restart;
		psenc->ch[psenc->chlen] = *s0++;
		psenc->chlen++;
		n--;
	}
	*s = s0;

	switch (cs) {
	case 3:
	case 2:
		/* skip SS2/SS3 */
		len = c - 1;
		s1 = &psenc->ch[1];
		break;
	case 1:
	case 0:
		len = c;
		s1 = &psenc->ch[0];
		break;
	default:
		goto encoding_error;
	}
	wchar = 0;
	while (len-- > 0)
		wchar = (wchar << 8) | (*s1++ & 0xff);
	wchar = (wchar & ~ei->mask) | ei->bits[cs];

	psenc->chlen = 0;
	if (pwc)
		*pwc = wchar;
	*nresult = wchar ? (size_t)(c - chlenbak) : 0;
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