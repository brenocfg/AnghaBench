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
typedef  int /*<<< orphan*/ * locale_t ;

/* Variables and functions */
 int /*<<< orphan*/ * LC_GLOBAL_LOCALE ; 
 int /*<<< orphan*/  __xlocale_global_locale ; 
 int /*<<< orphan*/  xlocale_release (int /*<<< orphan*/ *) ; 

void
freelocale(locale_t loc)
{

	/*
	 * Fail if we're passed something that isn't a locale. If we're
	 * passed the global locale, pretend that we freed it but don't
	 * actually do anything.
	 */
	if (loc != NULL && loc != LC_GLOBAL_LOCALE &&
	    loc != &__xlocale_global_locale)
		xlocale_release(loc);
}