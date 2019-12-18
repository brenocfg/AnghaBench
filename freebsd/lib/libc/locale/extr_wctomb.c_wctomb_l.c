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
struct TYPE_2__ {size_t (* __wcrtomb ) (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  wctomb; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 TYPE_1__* XLOCALE_CTYPE (int /*<<< orphan*/ ) ; 
 size_t stub1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
wctomb_l(char *s, wchar_t wchar, locale_t locale)
{
	static const mbstate_t initial;
	size_t rval;
	FIX_LOCALE(locale);

	if (s == NULL) {
		/* No support for state dependent encodings. */
		XLOCALE_CTYPE(locale)->wctomb = initial;
		return (0);
	}
	if ((rval = XLOCALE_CTYPE(locale)->__wcrtomb(s, wchar,
	    &(XLOCALE_CTYPE(locale)->wctomb))) == (size_t)-1)
		return (-1);
	return ((int)rval);
}