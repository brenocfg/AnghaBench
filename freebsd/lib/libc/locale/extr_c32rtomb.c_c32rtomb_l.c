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
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  locale_t ;
typedef  int char32_t ;
struct TYPE_2__ {int /*<<< orphan*/  c32rtomb; } ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 TYPE_1__* XLOCALE_CTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 size_t wcrtomb_l (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

size_t
c32rtomb_l(char * __restrict s, char32_t c32, mbstate_t * __restrict ps,
    locale_t locale)
{

	/* Unicode Standard 5.0, D90: ill-formed characters. */
	if ((c32 >= 0xd800 && c32 <= 0xdfff) || c32 > 0x10ffff) {
		errno = EILSEQ;
		return ((size_t)-1);
	}

	FIX_LOCALE(locale);
	if (ps == NULL)
		ps = &(XLOCALE_CTYPE(locale)->c32rtomb);

	/* Assume wchar_t uses UTF-32. */
	return (wcrtomb_l(s, c32, ps, locale));
}