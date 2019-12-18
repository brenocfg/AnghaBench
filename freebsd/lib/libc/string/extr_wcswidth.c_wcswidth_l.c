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
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 int wcwidth_l (int,int /*<<< orphan*/ ) ; 

int
wcswidth_l(const wchar_t *pwcs, size_t n, locale_t locale)
{
	wchar_t wc;
	int len, l;
	FIX_LOCALE(locale);

	len = 0;
	while (n-- > 0 && (wc = *pwcs++) != L'\0') {
		if ((l = wcwidth_l(wc, locale)) < 0)
			return (-1);
		len += l;
	}
	return (len);
}