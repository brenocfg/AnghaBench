#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lc_monetary_T {int dummy; } ;
struct xlocale_monetary {struct lc_monetary_T locale; } ;
typedef  TYPE_1__* locale_t ;
struct TYPE_3__ {scalar_t__* components; scalar_t__ using_monetary_locale; } ;

/* Variables and functions */
 size_t XLC_MONETARY ; 
 int /*<<< orphan*/  _C_monetary_locale ; 

struct lc_monetary_T *
__get_current_monetary_locale(locale_t loc)
{
	return (loc->using_monetary_locale
		? &((struct xlocale_monetary*)loc->components[XLC_MONETARY])->locale
		: (struct lc_monetary_T *)&_C_monetary_locale);
}