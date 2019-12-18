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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int __wcwidth_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
wcwidth_l(wchar_t wc, locale_t locale)
{
	return (__wcwidth_l(wc, locale));
}