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
struct TYPE_7__ {int chlen; int* ch; int current_endian; } ;
typedef  TYPE_1__ _UTF1632State ;
struct TYPE_8__ {int mode; int preffered_endian; } ;
typedef  TYPE_2__ _UTF1632EncodingInfo ;

/* Variables and functions */
 int EILSEQ ; 
#define  _ENDIAN_BIG 129 
#define  _ENDIAN_LITTLE 128 
 int _ENDIAN_UNKNOWN ; 
 int _MODE_FORCE_ENDIAN ; 
 int _MODE_UTF32 ; 
 int /*<<< orphan*/  _citrus_UTF1632_init_state (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static int
_citrus_UTF1632_mbrtowc_priv(_UTF1632EncodingInfo *ei, wchar_t *pwc,
    char **s, size_t n, _UTF1632State *psenc, size_t *nresult)
{
	char *s0;
	size_t result;
	wchar_t wc = L'\0';
	int chlenbak, endian, needlen;

	s0 = *s;

	if (s0 == NULL) {
		_citrus_UTF1632_init_state(ei, psenc);
		*nresult = 0; /* state independent */
		return (0);
	}

	result = 0;
	chlenbak = psenc->chlen;

refetch:
	needlen = ((ei->mode & _MODE_UTF32) != 0 || chlenbak >= 2) ? 4 : 2;

	while (chlenbak < needlen) {
		if (n == 0)
			goto restart;
		psenc->ch[chlenbak++] = *s0++;
		n--;
		result++;
	}

	/* judge endian marker */
	if ((ei->mode & _MODE_UTF32) == 0) {
		/* UTF16 */
		if (psenc->ch[0] == 0xFE && psenc->ch[1] == 0xFF) {
			psenc->current_endian = _ENDIAN_BIG;
			chlenbak = 0;
			goto refetch;
		} else if (psenc->ch[0] == 0xFF && psenc->ch[1] == 0xFE) {
			psenc->current_endian = _ENDIAN_LITTLE;
			chlenbak = 0;
			goto refetch;
		}
	} else {
		/* UTF32 */
		if (psenc->ch[0] == 0x00 && psenc->ch[1] == 0x00 &&
		    psenc->ch[2] == 0xFE && psenc->ch[3] == 0xFF) {
			psenc->current_endian = _ENDIAN_BIG;
			chlenbak = 0;
			goto refetch;
		} else if (psenc->ch[0] == 0xFF && psenc->ch[1] == 0xFE &&
			   psenc->ch[2] == 0x00 && psenc->ch[3] == 0x00) {
			psenc->current_endian = _ENDIAN_LITTLE;
			chlenbak = 0;
			goto refetch;
		}
	}
	endian = ((ei->mode & _MODE_FORCE_ENDIAN) != 0 ||
	    psenc->current_endian == _ENDIAN_UNKNOWN) ? ei->preffered_endian :
	    psenc->current_endian;

	/* get wc */
	if ((ei->mode & _MODE_UTF32) == 0) {
		/* UTF16 */
		if (needlen == 2) {
			switch (endian) {
			case _ENDIAN_LITTLE:
				wc = (psenc->ch[0] |
				    ((wchar_t)psenc->ch[1] << 8));
				break;
			case _ENDIAN_BIG:
				wc = (psenc->ch[1] |
				    ((wchar_t)psenc->ch[0] << 8));
				break;
			default:
				goto ilseq;
			}
			if (wc >= 0xD800 && wc <= 0xDBFF) {
				/* surrogate high */
				needlen = 4;
				goto refetch;
			}
		} else {
			/* surrogate low */
			wc -= 0xD800; /* wc : surrogate high (see above) */
			wc <<= 10;
			switch (endian) {
			case _ENDIAN_LITTLE:
				if (psenc->ch[3] < 0xDC || psenc->ch[3] > 0xDF)
					goto ilseq;
				wc |= psenc->ch[2];
				wc |= (wchar_t)(psenc->ch[3] & 3) << 8;
				break;
			case _ENDIAN_BIG:
				if (psenc->ch[2]<0xDC || psenc->ch[2]>0xDF)
					goto ilseq;
				wc |= psenc->ch[3];
				wc |= (wchar_t)(psenc->ch[2] & 3) << 8;
				break;
			default:
				goto ilseq;
			}
			wc += 0x10000;
		}
	} else {
		/* UTF32 */
		switch (endian) {
		case _ENDIAN_LITTLE:
			wc = (psenc->ch[0] |
			    ((wchar_t)psenc->ch[1] << 8) |
			    ((wchar_t)psenc->ch[2] << 16) |
			    ((wchar_t)psenc->ch[3] << 24));
			break;
		case _ENDIAN_BIG:
			wc = (psenc->ch[3] |
			    ((wchar_t)psenc->ch[2] << 8) |
			    ((wchar_t)psenc->ch[1] << 16) |
			    ((wchar_t)psenc->ch[0] << 24));
			break;
		default:
			goto ilseq;
		}
		if (wc >= 0xD800 && wc <= 0xDFFF)
			goto ilseq;
	}


	*pwc = wc;
	psenc->chlen = 0;
	*nresult = result;
	*s = s0;

	return (0);

ilseq:
	*nresult = (size_t)-1;
	psenc->chlen = 0;
	return (EILSEQ);

restart:
	*nresult = (size_t)-2;
	psenc->chlen = chlenbak;
	*s = s0;
	return (0);
}