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
typedef  int /*<<< orphan*/  wctrans_t ;

/* Variables and functions */
 int /*<<< orphan*/  __get_locale () ; 
 int /*<<< orphan*/  towctrans_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

wint_t
towctrans(wint_t wc, wctrans_t desc)
{
	return towctrans_l(wc, desc, __get_locale());
}