#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ wchar_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  _UTF7State ;
typedef  int /*<<< orphan*/  _UTF7EncodingInfo ;

/* Variables and functions */
 int EILSEQ ; 
 scalar_t__ HISRG_MIN ; 
 scalar_t__ LOSRG_MIN ; 
 scalar_t__ SRG_BASE ; 
 int UINT32_C (int) ; 
 int UTF16_MAX ; 
 int UTF32_MAX ; 
 int _citrus_UTF7_utf16tomb (int /*<<< orphan*/ *,char*,size_t,scalar_t__,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int
_citrus_UTF7_wcrtomb_priv(_UTF7EncodingInfo * __restrict ei,
    char * __restrict s, size_t n, wchar_t wchar,
    _UTF7State * __restrict psenc, size_t * __restrict nresult)
{
	uint32_t u32;
	uint16_t u16[2];
	int err, i, len;
	size_t nr, siz;

	u32 = (uint32_t)wchar;
	if (u32 <= UTF16_MAX) {
		u16[0] = (uint16_t)u32;
		len = 1;
	} else if (u32 <= UTF32_MAX) {
		u32 -= SRG_BASE;
		u16[0] = (u32 >> 10) + HISRG_MIN;
		u16[1] = ((uint16_t)(u32 & UINT32_C(0x3ff))) + LOSRG_MIN;
		len = 2;
	} else {
		*nresult = (size_t)-1;
		return (EILSEQ);
	}
	siz = 0;
	for (i = 0; i < len; ++i) {
		err = _citrus_UTF7_utf16tomb(ei, s, n, u16[i], psenc, &nr);
		if (err != 0)
			return (err); /* XXX: state has been modified */
		s += nr;
		n -= nr;
		siz += nr;
	}
	*nresult = siz;

	return (0);
}