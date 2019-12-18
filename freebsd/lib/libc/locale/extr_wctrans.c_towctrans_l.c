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
typedef  int /*<<< orphan*/  wint_t ;
typedef  int wctrans_t ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  _WCT_ERROR 130 
#define  _WCT_TOLOWER 129 
#define  _WCT_TOUPPER 128 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  towlower_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  towupper_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

wint_t
towctrans_l(wint_t wc, wctrans_t desc, locale_t locale)
{
	switch (desc) {
	case _WCT_TOLOWER:
		wc = towlower_l(wc, locale);
		break;
	case _WCT_TOUPPER:
		wc = towupper_l(wc, locale);
		break;
	case _WCT_ERROR:
	default:
		errno = EINVAL;
		break;
	}

	return (wc);
}