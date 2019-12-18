#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
typedef  unsigned char uint8_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
struct TYPE_2__ {int want; int ch; } ;
typedef  TYPE_1__ _EucState ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  EINVAL ; 
 int MB_CUR_MAX ; 
 int MIN (int,size_t) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static size_t
_EUC_mbrtowc_impl(wchar_t * __restrict pwc, const char * __restrict s,
	size_t n, mbstate_t * __restrict ps,
	uint8_t cs2, uint8_t cs2width, uint8_t cs3, uint8_t cs3width)
{
	_EucState *es;
	int i, want;
	wchar_t wc = 0;
	unsigned char ch, chs;

	es = (_EucState *)ps;

	if (es->want < 0 || es->want > MB_CUR_MAX) {
		errno = EINVAL;
		return ((size_t)-1);
	}

	if (s == NULL) {
		s = "";
		n = 1;
		pwc = NULL;
	}

	if (n == 0)
		/* Incomplete multibyte sequence */
		return ((size_t)-2);

	if (es->want == 0) {
		/* Fast path for plain ASCII (CS0) */
		if (((ch = (unsigned char)*s) & 0x80) == 0) {
			if (pwc != NULL)
				*pwc = ch;
			return (ch != '\0' ? 1 : 0);
		}

		if (ch >= 0xa1) {
			/* CS1 */
			want = 2;
		} else if (ch == cs2) {
			want = cs2width;
		} else if (ch == cs3) {
			want = cs3width;
		} else {
			errno = EILSEQ;
			return ((size_t)-1);
		}


		es->want = want;
		es->ch = 0;
	} else {
		want = es->want;
		wc = es->ch;
	}

	for (i = 0; i < MIN(want, n); i++) {
		wc <<= 8;
		chs = *s;
		wc |= chs;
		s++;
	}
	if (i < want) {
		/* Incomplete multibyte sequence */
		es->want = want - i;
		es->ch = wc;
		errno = EILSEQ;
		return ((size_t)-2);
	}
	if (pwc != NULL)
		*pwc = wc;
	es->want = 0;
	return (wc == L'\0' ? 0 : want);
}