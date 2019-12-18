#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wchar_t ;
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct TYPE_5__ {int chlen; } ;
typedef  TYPE_1__ _UTF7State ;
typedef  int /*<<< orphan*/  _UTF7EncodingInfo ;

/* Variables and functions */
 int EILSEQ ; 
 int HISRG_MAX ; 
 int HISRG_MIN ; 
 int LOSRG_MAX ; 
 int LOSRG_MIN ; 
 scalar_t__ SRG_BASE ; 
 scalar_t__ _ENCODING_IS_STATE_DEPENDENT ; 
 int /*<<< orphan*/  _citrus_UTF7_init_state (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int _citrus_UTF7_mbtoutf16 (int /*<<< orphan*/ *,int*,char**,size_t,TYPE_1__*,size_t*) ; 

__attribute__((used)) static int
_citrus_UTF7_mbrtowc_priv(_UTF7EncodingInfo * __restrict ei,
    wchar_t * __restrict pwc, char ** __restrict s, size_t n,
    _UTF7State * __restrict psenc, size_t * __restrict nresult)
{
	uint32_t u32;
	uint16_t hi, lo;
	size_t nr, siz;
	int err;

	if (*s == NULL) {
		_citrus_UTF7_init_state(ei, psenc);
		*nresult = (size_t)_ENCODING_IS_STATE_DEPENDENT;
		return (0);
	}
	err = _citrus_UTF7_mbtoutf16(ei, &hi, s, n, psenc, &nr);
	if (nr == (size_t)-1 || nr == (size_t)-2) {
		*nresult = nr;
		return (err);
	}
	if (err != 0)
		return (err);
	n -= nr;
	siz = nr;
	if (hi < HISRG_MIN || hi > HISRG_MAX) {
		u32 = (uint32_t)hi;
		goto done;
	}
	err = _citrus_UTF7_mbtoutf16(ei, &lo, s, n, psenc, &nr);
	if (nr == (size_t)-1 || nr == (size_t)-2) {
		psenc->chlen = 1; /* make get_state_desc return incomplete */
		*nresult = nr;
		return (err);
	}
	if (err != 0)
		return (err);
	if (lo < LOSRG_MIN || lo > LOSRG_MAX) {
		*nresult = (size_t)-1;
		return (EILSEQ);
	}
	hi -= HISRG_MIN;
	lo -= LOSRG_MIN;
	u32 = (hi << 10 | lo) + SRG_BASE;
	siz += nr;
done:
	if (pwc != NULL)
		*pwc = (wchar_t)u32;
	if (u32 == (uint32_t)0) {
		*nresult = (size_t)0;
		_citrus_UTF7_init_state(ei, psenc);
	} else {
		*nresult = siz;
	}
	return (err);
}