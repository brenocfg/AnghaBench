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
 int /*<<< orphan*/  __has_thread_locale ; 
 int /*<<< orphan*/ * __thread_locale ; 
 int /*<<< orphan*/  __xlocale_global_locale ; 

__attribute__((used)) static inline locale_t __get_locale(void)
{

	if (!__has_thread_locale) {
		return (&__xlocale_global_locale);
	}
	return (__thread_locale ? __thread_locale : &__xlocale_global_locale);
}