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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_2__ {int /*<<< orphan*/  decimal_point; } ;

/* Variables and functions */
 int /*<<< orphan*/  MB_CUR_MAX ; 
 int /*<<< orphan*/  initial_mbs ; 
 TYPE_1__* localeconv_l (int /*<<< orphan*/ ) ; 
 int mbrtowc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline wchar_t
get_decpt(locale_t locale)
{
	mbstate_t mbs;
	wchar_t decpt;
	int nconv;

	mbs = initial_mbs;
	nconv = mbrtowc(&decpt, localeconv_l(locale)->decimal_point, MB_CUR_MAX, &mbs);
	if (nconv == (size_t)-1 || nconv == (size_t)-2)
		decpt = '.';    /* failsafe */
	return (decpt);
}