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
typedef  scalar_t__ wchar_t ;
struct TYPE_4__ {int chlen; int* ch; } ;
typedef  TYPE_1__ _JOHABState ;
typedef  int /*<<< orphan*/  _JOHABEncodingInfo ;

/* Variables and functions */
 int EILSEQ ; 
 int EINVAL ; 
 size_t _ENCODING_IS_STATE_DEPENDENT ; 
 int /*<<< orphan*/  _citrus_JOHAB_init_state (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ishangul (int,int) ; 
 int /*<<< orphan*/  ishanja (int,int) ; 
 int /*<<< orphan*/  isuda (int,int) ; 

__attribute__((used)) static int
/*ARGSUSED*/
_citrus_JOHAB_mbrtowc_priv(_JOHABEncodingInfo * __restrict ei,
    wchar_t * __restrict pwc, char ** __restrict s, size_t n,
    _JOHABState * __restrict psenc, size_t * __restrict nresult)
{
	char *s0;
	int l, t;

	if (*s == NULL) {
		_citrus_JOHAB_init_state(ei, psenc);
		*nresult = _ENCODING_IS_STATE_DEPENDENT;
		return (0);
	}
	s0 = *s;

	switch (psenc->chlen) {
	case 0:
		if (n-- < 1)
			goto restart;
		l = *s0++ & 0xFF;
		if (l <= 0x7F) {
			if (pwc != NULL)
				*pwc = (wchar_t)l;
			*nresult = (l == 0) ? 0 : 1;
			*s = s0;
			return (0);
		}
		psenc->ch[psenc->chlen++] = l;
		break;
	case 1:
		l = psenc->ch[0] & 0xFF;
		break;
	default:
		return (EINVAL);
	}
	if (n-- < 1) {
restart:
		*nresult = (size_t)-2;
		*s = s0;
		return (0);
	}
	t = *s0++ & 0xFF;
	if (!ishangul(l, t) && !isuda(l, t) && !ishanja(l, t)) {
		*nresult = (size_t)-1;
		return (EILSEQ);
	}
	if (pwc != NULL)
		*pwc = (wchar_t)(l << 8 | t);
	*nresult = s0 - *s;
	*s = s0;
	psenc->chlen = 0;

	return (0);
}