#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t wint_t ;
typedef  int wctype_t ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_5__ {size_t __nranges; TYPE_3__* __ranges; } ;
typedef  TYPE_1__ _RuneRange ;
struct TYPE_6__ {int* __runetype; TYPE_1__ __runetype_ext; } ;
typedef  TYPE_2__ _RuneLocale ;
struct TYPE_7__ {size_t __min; size_t __max; int* __types; int __map; } ;
typedef  TYPE_3__ _RuneEntry ;
struct TYPE_8__ {TYPE_2__* runes; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 TYPE_4__* XLOCALE_CTYPE (int /*<<< orphan*/ ) ; 
 size_t _CACHED_RUNES ; 

wint_t
nextwctype_l(wint_t wc, wctype_t wct, locale_t locale)
{
	size_t lim;
	FIX_LOCALE(locale);
	_RuneLocale *runes = XLOCALE_CTYPE(locale)->runes;
	_RuneRange *rr = &runes->__runetype_ext;
	_RuneEntry *base, *re;
	int noinc;

	noinc = 0;
	if (wc < _CACHED_RUNES) {
		wc++;
		while (wc < _CACHED_RUNES) {
			if (runes->__runetype[wc] & wct)
				return (wc);
			wc++;
		}
		wc--;
	}
	if (rr->__ranges != NULL && wc < rr->__ranges[0].__min) {
		wc = rr->__ranges[0].__min;
		noinc = 1;
	}

	/* Binary search -- see bsearch.c for explanation. */
	base = rr->__ranges;
	for (lim = rr->__nranges; lim != 0; lim >>= 1) {
		re = base + (lim >> 1);
		if (re->__min <= wc && wc <= re->__max)
			goto found;
		else if (wc > re->__max) {
			base = re + 1;
			lim--;
		}
	}
	return (-1);
found:
	if (!noinc)
		wc++;
	if (re->__min <= wc && wc <= re->__max) {
		if (re->__types != NULL) {
			for (; wc <= re->__max; wc++)
				if (re->__types[wc - re->__min] & wct)
					return (wc);
		} else if (re->__map & wct)
			return (wc);
	}
	while (++re < rr->__ranges + rr->__nranges) {
		wc = re->__min;
		if (re->__types != NULL) {
			for (; wc <= re->__max; wc++)
				if (re->__types[wc - re->__min] & wct)
					return (wc);
		} else if (re->__map & wct)
			return (wc);
	}
	return (-1);
}