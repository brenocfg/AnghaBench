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
typedef  int /*<<< orphan*/  wint_t ;
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_2__ {int (* __mbrtowc ) (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEOF ; 
 TYPE_1__* XLOCALE_CTYPE (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 

wint_t
btowc_l(int c, locale_t l)
{
	static const mbstate_t initial;
	mbstate_t mbs = initial;
	char cc;
	wchar_t wc;
	FIX_LOCALE(l);

	if (c == EOF)
		return (WEOF);
	/*
	 * We expect mbrtowc() to return 0 or 1, hence the check for n > 1
	 * which detects error return values as well as "impossible" byte
	 * counts.
	 */
	cc = (char)c;
	if (XLOCALE_CTYPE(l)->__mbrtowc(&wc, &cc, 1, &mbs) > 1)
		return (WEOF);
	return (wc);
}