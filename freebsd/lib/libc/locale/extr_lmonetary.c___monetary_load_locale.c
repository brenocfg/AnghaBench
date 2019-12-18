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
struct TYPE_2__ {int /*<<< orphan*/  monetary_locale_changed; int /*<<< orphan*/  using_monetary_locale; } ;

/* Variables and functions */
 TYPE_1__ __xlocale_global_locale ; 
 int /*<<< orphan*/  __xlocale_global_monetary ; 
 int monetary_load_locale_l (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

int
__monetary_load_locale(const char *name)
{
	return monetary_load_locale_l(&__xlocale_global_monetary,
			&__xlocale_global_locale.using_monetary_locale,
			&__xlocale_global_locale.monetary_locale_changed, name);
}