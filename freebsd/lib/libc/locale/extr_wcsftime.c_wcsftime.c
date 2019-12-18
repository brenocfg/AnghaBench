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
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __get_locale () ; 
 size_t wcsftime_l (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*,struct tm const*,int /*<<< orphan*/ ) ; 

size_t
wcsftime(wchar_t * __restrict wcs, size_t maxsize,
	const wchar_t * __restrict format, const struct tm * __restrict timeptr)
{
	return wcsftime_l(wcs, maxsize, format, timeptr, __get_locale());
}