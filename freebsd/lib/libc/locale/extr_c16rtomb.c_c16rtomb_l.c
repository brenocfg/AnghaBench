#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  locale_t ;
typedef  int char32_t ;
typedef  int char16_t ;
struct TYPE_3__ {int lead_surrogate; int /*<<< orphan*/  c32_mbstate; } ;
typedef  TYPE_1__ _Char16State ;
struct TYPE_4__ {int /*<<< orphan*/  c16rtomb; } ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 TYPE_2__* XLOCALE_CTYPE (int /*<<< orphan*/ ) ; 
 size_t c32rtomb_l (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

size_t
c16rtomb_l(char * __restrict s, char16_t c16, mbstate_t * __restrict ps,
    locale_t locale)
{
	_Char16State *cs;
	char32_t c32;

	FIX_LOCALE(locale);
	if (ps == NULL)
		ps = &(XLOCALE_CTYPE(locale)->c16rtomb);
	cs = (_Char16State *)ps;

	/* If s is a null pointer, the value of parameter c16 is ignored. */
	if (s == NULL) {
		c32 = 0;
	} else if (cs->lead_surrogate >= 0xd800 &&
	    cs->lead_surrogate <= 0xdbff) {
		/* We should see a trail surrogate now. */
		if (c16 < 0xdc00 || c16 > 0xdfff) {
			errno = EILSEQ;
			return ((size_t)-1);
		}
		c32 = 0x10000 + ((cs->lead_surrogate & 0x3ff) << 10 |
		    (c16 & 0x3ff));
	} else if (c16 >= 0xd800 && c16 <= 0xdbff) {
		/* Store lead surrogate for next invocation. */
		cs->lead_surrogate = c16;
		return (0);
	} else {
		/* Regular character. */
		c32 = c16;
	}
	cs->lead_surrogate = 0;

	return (c32rtomb_l(s, c32, &cs->c32_mbstate, locale));
}