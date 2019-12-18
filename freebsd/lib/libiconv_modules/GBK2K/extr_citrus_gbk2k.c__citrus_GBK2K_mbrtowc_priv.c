#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
struct TYPE_5__ {int chlen; char* ch; } ;
typedef  TYPE_1__ _GBK2KState ;
struct TYPE_6__ {int mb_cur_max; } ;
typedef  TYPE_2__ _GBK2KEncodingInfo ;

/* Variables and functions */
 int EILSEQ ; 
 int EINVAL ; 
 int /*<<< orphan*/  _PSENC ; 
 int /*<<< orphan*/  _PUSH_PSENC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mb_leadbyte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mb_singlebyte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mb_surrogate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mb_trailbyte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_citrus_GBK2K_mbrtowc_priv(_GBK2KEncodingInfo * __restrict ei,
    wchar_t * __restrict pwc, char ** __restrict s, size_t n,
    _GBK2KState * __restrict psenc, size_t * __restrict nresult)
{
	char *s0, *s1;
	wchar_t wc;
	int chlenbak, len;

	s0 = *s;

	if (s0 == NULL) {
		/* _citrus_GBK2K_init_state(ei, psenc); */
		psenc->chlen = 0;
		*nresult = 0;
		return (0);
	}

	chlenbak = psenc->chlen;

	switch (psenc->chlen) {
	case 3:
		if (!_mb_leadbyte (_PSENC))
			goto invalid;
	/* FALLTHROUGH */
	case 2:
		if (!_mb_surrogate(_PSENC) || _mb_trailbyte(_PSENC))
			goto invalid;
	/* FALLTHROUGH */
	case 1:
		if (!_mb_leadbyte (_PSENC))
			goto invalid;
	/* FALLTHOROUGH */
	case 0:
		break;
	default:
		goto invalid;
	}

	for (;;) {
		if (n-- < 1)
			goto restart;

		_PUSH_PSENC(*s0++);

		switch (psenc->chlen) {
		case 1:
			if (_mb_singlebyte(_PSENC))
				goto convert;
			if (_mb_leadbyte  (_PSENC))
				continue;
			goto ilseq;
		case 2:
			if (_mb_trailbyte (_PSENC))
				goto convert;
			if (ei->mb_cur_max == 4 &&
			    _mb_surrogate (_PSENC))
				continue;
			goto ilseq;
		case 3:
			if (_mb_leadbyte  (_PSENC))
				continue;
			goto ilseq;
		case 4:
			if (_mb_surrogate (_PSENC))
				goto convert;
			goto ilseq;
		}
	}

convert:
	len = psenc->chlen;
	s1  = &psenc->ch[0];
	wc  = 0;
	while (len-- > 0)
		wc = (wc << 8) | (*s1++ & 0xff);

	if (pwc != NULL)
		*pwc = wc;
	*s = s0;
	*nresult = (wc == 0) ? 0 : psenc->chlen - chlenbak;
	/* _citrus_GBK2K_init_state(ei, psenc); */
	psenc->chlen = 0;

	return (0);

restart:
	*s = s0;
	*nresult = (size_t)-2;

	return (0);

invalid:
	return (EINVAL);

ilseq:
	*nresult = (size_t)-1;
	return (EILSEQ);
}