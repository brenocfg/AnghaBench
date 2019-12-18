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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_4__ {int chlen; int* ch; } ;
typedef  TYPE_1__ _DECHanyuState ;
typedef  int /*<<< orphan*/  _DECHanyuEncodingInfo ;

/* Variables and functions */
 int EILSEQ ; 
 int EINVAL ; 
 scalar_t__ HANYUBIT ; 
 size_t _ENCODING_IS_STATE_DEPENDENT ; 
 int /*<<< orphan*/  _citrus_DECHanyu_init_state (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  is_hanyu1 (int) ; 
 int /*<<< orphan*/  is_hanyu2 (int) ; 
 int /*<<< orphan*/  is_leadbyte (int) ; 
 int /*<<< orphan*/  is_singlebyte (int) ; 
 int /*<<< orphan*/  is_trailbyte (int) ; 

__attribute__((used)) static int
/*ARGSUSED*/
_citrus_DECHanyu_mbrtowc_priv(_DECHanyuEncodingInfo * __restrict ei,
    wchar_t * __restrict pwc, char ** __restrict s, size_t n,
    _DECHanyuState * __restrict psenc, size_t * __restrict nresult)
{
	char *s0;
	wchar_t wc;
	int ch;

	if (*s == NULL) {
		_citrus_DECHanyu_init_state(ei, psenc);
		*nresult = _ENCODING_IS_STATE_DEPENDENT;
		return (0);
	}
	s0 = *s;

	wc = (wchar_t)0;
	switch (psenc->chlen) {
	case 0:
		if (n-- < 1)
			goto restart;
		ch = *s0++ & 0xFF;
		if (is_singlebyte(ch)) {
			if (pwc != NULL)
				*pwc = (wchar_t)ch;
			*nresult = (size_t)((ch == 0) ? 0 : 1);
			*s = s0;
			return (0);
		}
		if (!is_leadbyte(ch))
			goto ilseq;
		psenc->ch[psenc->chlen++] = ch;
		break;
	case 1:
		ch = psenc->ch[0] & 0xFF;
		if (!is_leadbyte(ch))
			return (EINVAL);
		break;
	case 2: case 3:
		ch = psenc->ch[0] & 0xFF;
		if (is_hanyu1(ch)) {
			ch = psenc->ch[1] & 0xFF;
			if (is_hanyu2(ch)) {
				wc |= (wchar_t)HANYUBIT;
				break;
			}
		}
	/*FALLTHROUGH*/
	default:
		return (EINVAL);
	}

	switch (psenc->chlen) {
	case 1:
		if (is_hanyu1(ch)) {
			if (n-- < 1)
				goto restart;
			ch = *s0++ & 0xFF;
			if (!is_hanyu2(ch))
				goto ilseq;
			psenc->ch[psenc->chlen++] = ch;
			wc |= (wchar_t)HANYUBIT;
			if (n-- < 1)
				goto restart;
			ch = *s0++ & 0xFF;
			if (!is_leadbyte(ch))
				goto ilseq;
			psenc->ch[psenc->chlen++] = ch;
		}
		break;
	case 2:
		if (n-- < 1)
			goto restart;
		ch = *s0++ & 0xFF;
		if (!is_leadbyte(ch))
			goto ilseq;
		psenc->ch[psenc->chlen++] = ch;
		break;
	case 3:
		ch = psenc->ch[2] & 0xFF;
		if (!is_leadbyte(ch))
			return (EINVAL);
	}
	if (n-- < 1)
		goto restart;
	wc |= (wchar_t)(ch << 8);
	ch = *s0++ & 0xFF;
	if (!is_trailbyte(ch))
		goto ilseq;
	wc |= (wchar_t)ch;
	if (pwc != NULL)
		*pwc = wc;
	*nresult = (size_t)(s0 - *s);
	*s = s0;
	psenc->chlen = 0;

	return (0);

restart:
	*nresult = (size_t)-2;
	*s = s0;
	return (0);

ilseq:
	*nresult = (size_t)-1;
	return (EILSEQ);
}