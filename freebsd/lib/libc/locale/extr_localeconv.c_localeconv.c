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
struct lconv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __get_locale () ; 
 struct lconv* localeconv_l (int /*<<< orphan*/ ) ; 

struct lconv *
localeconv(void)
{
	return localeconv_l(__get_locale());
}