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
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  __get_locale () ; 
 int /*<<< orphan*/  wcstoimax_l (int /*<<< orphan*/  const*,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 

intmax_t
wcstoimax(const wchar_t * __restrict nptr, wchar_t ** __restrict endptr,
    int base)
{
	return wcstoimax_l(nptr, endptr, base, __get_locale());
}