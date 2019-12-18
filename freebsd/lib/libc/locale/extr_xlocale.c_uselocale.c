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
 int /*<<< orphan*/ * get_thread_locale () ; 
 int /*<<< orphan*/  set_thread_locale (int /*<<< orphan*/ *) ; 

locale_t uselocale(locale_t loc)
{
	locale_t old = get_thread_locale();
	if (NULL != loc) {
		set_thread_locale(loc);
	}
	return (old ? old : LC_GLOBAL_LOCALE);
}