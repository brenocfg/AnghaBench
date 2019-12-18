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
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ *) ; 
 int XLC_LAST ; 
 int /*<<< orphan*/  _once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * alloc_locale () ; 
 int /*<<< orphan*/  copyflags (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dupcomponent (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_key ; 
 int /*<<< orphan*/  once_control ; 

locale_t duplocale(locale_t base)
{
	locale_t new = alloc_locale();
	int type;

	_once(&once_control, init_key);

	if (NULL == new) {
		return (NULL);
	}
	
	FIX_LOCALE(base);
	copyflags(new, base);

	for (type=0 ; type<XLC_LAST ; type++) {
		dupcomponent(type, base, new);
	}

	return (new);
}