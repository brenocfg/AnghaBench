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
typedef  scalar_t__ wchar_t ;
typedef  int uint32_t ;
struct TYPE_5__ {size_t chlen; char* ch; } ;
typedef  TYPE_1__ _UESState ;
struct TYPE_6__ {int mode; } ;
typedef  TYPE_2__ _UESEncodingInfo ;

/* Variables and functions */
 int BMP_MAX ; 
 int E2BIG ; 
 int EILSEQ ; 
 int EINVAL ; 
 int MODE_C99 ; 
 int /*<<< orphan*/  UCS2_BIT ; 
 int UCS2_MAX ; 
 int /*<<< orphan*/  UCS4_BIT ; 
 int UCS4_MAX ; 
 int is_basic (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 void* to_str (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucs_to_surrogate (scalar_t__,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int
_citrus_UES_wcrtomb_priv(_UESEncodingInfo * __restrict ei,
    char * __restrict s, size_t n, wchar_t wc,
    _UESState * __restrict psenc, size_t * __restrict nresult)
{
	wchar_t hi, lo;

	if (psenc->chlen != 0)
		return (EINVAL);

	if ((ei->mode & MODE_C99) ? is_basic(wc) : (uint32_t)wc <= 0x7F) {
		if (n-- < 1)
			goto e2big;
		psenc->ch[psenc->chlen++] = (char)wc;
	} else if ((uint32_t)wc <= BMP_MAX) {
		if (n < 6)
			goto e2big;
		psenc->chlen = to_str(&psenc->ch[0], wc, UCS2_BIT);
	} else if ((ei->mode & MODE_C99) == 0 && (uint32_t)wc <= UCS2_MAX) {
		if (n < 12)
			goto e2big;
		ucs_to_surrogate(wc, &hi, &lo);
		psenc->chlen += to_str(&psenc->ch[0], hi, UCS2_BIT);
		psenc->chlen += to_str(&psenc->ch[6], lo, UCS2_BIT);
	} else if ((ei->mode & MODE_C99) && (uint32_t)wc <= UCS4_MAX) {
		if (n < 10)
			goto e2big;
		psenc->chlen = to_str(&psenc->ch[0], wc, UCS4_BIT);
	} else {
		*nresult = (size_t)-1;
		return (EILSEQ);
	}
	memcpy(s, psenc->ch, psenc->chlen);
	*nresult = psenc->chlen;
	psenc->chlen = 0;

	return (0);

e2big:
	*nresult = (size_t)-1;
	return (E2BIG);
}