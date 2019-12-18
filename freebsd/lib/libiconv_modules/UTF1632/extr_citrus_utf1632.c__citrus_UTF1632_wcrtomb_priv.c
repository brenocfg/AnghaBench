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
struct TYPE_5__ {int current_endian; } ;
typedef  TYPE_1__ _UTF1632State ;
struct TYPE_6__ {int mode; int preffered_endian; } ;
typedef  TYPE_2__ _UTF1632EncodingInfo ;

/* Variables and functions */
 int E2BIG ; 
 int EILSEQ ; 
#define  _ENDIAN_BIG 129 
#define  _ENDIAN_LITTLE 128 
 int _ENDIAN_UNKNOWN ; 
 int _MODE_FORCE_ENDIAN ; 
 int _MODE_UTF32 ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static int
_citrus_UTF1632_wcrtomb_priv(_UTF1632EncodingInfo *ei, char *s, size_t n,
    wchar_t wc, _UTF1632State *psenc, size_t *nresult)
{
	wchar_t wc2;
	static const char _bom[4] = {
	    0x00, 0x00, 0xFE, 0xFF,
	};
	const char *bom = &_bom[0];
	size_t cnt;

	cnt = (size_t)0;
	if (psenc->current_endian == _ENDIAN_UNKNOWN) {
		if ((ei->mode & _MODE_FORCE_ENDIAN) == 0) {
			if (ei->mode & _MODE_UTF32)
				cnt = 4;
			else {
				cnt = 2;
				bom += 2;
			}
			if (n < cnt)
				goto e2big;
			memcpy(s, bom, cnt);
			s += cnt, n -= cnt;
		}
		psenc->current_endian = ei->preffered_endian;
	}

	wc2 = 0;
	if ((ei->mode & _MODE_UTF32)==0) {
		/* UTF16 */
		if (wc > 0xFFFF) {
			/* surrogate */
			if (wc > 0x10FFFF)
				goto ilseq;
			if (n < 4)
				goto e2big;
			cnt += 4;
			wc -= 0x10000;
			wc2 = (wc & 0x3FF) | 0xDC00;
			wc = (wc>>10) | 0xD800;
		} else {
			if (n < 2)
				goto e2big;
			cnt += 2;
		}

surrogate:
		switch (psenc->current_endian) {
		case _ENDIAN_BIG:
			s[1] = wc;
			s[0] = (wc >>= 8);
			break;
		case _ENDIAN_LITTLE:
			s[0] = wc;
			s[1] = (wc >>= 8);
			break;
		}
		if (wc2 != 0) {
			wc = wc2;
			wc2 = 0;
			s += 2;
			goto surrogate;
		}
	} else {
		/* UTF32 */
		if (wc >= 0xD800 && wc <= 0xDFFF)
			goto ilseq;
		if (n < 4)
			goto e2big;
		cnt += 4;
		switch (psenc->current_endian) {
		case _ENDIAN_BIG:
			s[3] = wc;
			s[2] = (wc >>= 8);
			s[1] = (wc >>= 8);
			s[0] = (wc >>= 8);
			break;
		case _ENDIAN_LITTLE:
			s[0] = wc;
			s[1] = (wc >>= 8);
			s[2] = (wc >>= 8);
			s[3] = (wc >>= 8);
			break;
		}
	}
	*nresult = cnt;

	return (0);

ilseq:
	*nresult = (size_t)-1;
	return (EILSEQ);
e2big:
	*nresult = (size_t)-1;
	return (E2BIG);
}