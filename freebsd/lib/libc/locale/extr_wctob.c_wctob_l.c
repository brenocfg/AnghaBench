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
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_2__ {int (* __wcrtomb ) (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 int MB_LEN_MAX ; 
 int /*<<< orphan*/  WEOF ; 
 TYPE_1__* XLOCALE_CTYPE (int /*<<< orphan*/ ) ; 
 int stub1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
wctob_l(wint_t c, locale_t locale)
{
	static const mbstate_t initial;
	mbstate_t mbs = initial;
	char buf[MB_LEN_MAX];
	FIX_LOCALE(locale);

	if (c == WEOF || XLOCALE_CTYPE(locale)->__wcrtomb(buf, c, &mbs) != 1)
		return (EOF);
	return ((unsigned char)*buf);
}