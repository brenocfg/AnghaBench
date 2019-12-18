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
struct TYPE_2__ {size_t (* __mbsnrtowcs ) (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ;int /*<<< orphan*/  mbsrtowcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZE_T_MAX ; 
 TYPE_1__* XLOCALE_CTYPE (int /*<<< orphan*/ ) ; 
 size_t stub1 (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

size_t
mbsrtowcs_l(wchar_t * __restrict dst, const char ** __restrict src, size_t len,
    mbstate_t * __restrict ps, locale_t locale)
{
	FIX_LOCALE(locale);
	if (ps == NULL)
		ps = &(XLOCALE_CTYPE(locale)->mbsrtowcs);
	return (XLOCALE_CTYPE(locale)->__mbsnrtowcs(dst, src, SIZE_T_MAX, len, ps));
}