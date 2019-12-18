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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_2__ {size_t (* __wcsnrtombs ) (char*,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZE_T_MAX ; 
 TYPE_1__* XLOCALE_CTYPE (int /*<<< orphan*/ ) ; 
 size_t stub1 (char*,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

size_t
wcstombs_l(char * __restrict s, const wchar_t * __restrict pwcs, size_t n,
		locale_t locale)
{
	static const mbstate_t initial;
	mbstate_t mbs;
	const wchar_t *pwcsp;
	FIX_LOCALE(locale);

	mbs = initial;
	pwcsp = pwcs;
	return (XLOCALE_CTYPE(locale)->__wcsnrtombs(s, &pwcsp, SIZE_T_MAX, n, &mbs));
}