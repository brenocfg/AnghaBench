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
typedef  int /*<<< orphan*/ * locale_t ;
struct TYPE_2__ {int /*<<< orphan*/ * runes; } ;

/* Variables and functions */
 int /*<<< orphan*/ * LC_GLOBAL_LOCALE ; 
 TYPE_1__* XLOCALE_CTYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _DefaultRuneLocale ; 
 int /*<<< orphan*/ * _ThreadRuneLocale ; 

void
__set_thread_rune_locale(locale_t loc)
{

	if (loc == NULL) {
		_ThreadRuneLocale = &_DefaultRuneLocale;
	} else if (loc == LC_GLOBAL_LOCALE) {
		_ThreadRuneLocale = 0;
	} else {
		_ThreadRuneLocale = XLOCALE_CTYPE(loc)->runes;
	}
}