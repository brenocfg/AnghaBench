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
typedef  TYPE_1__* locale_t ;
struct TYPE_2__ {void* csym; scalar_t__* components; } ;

/* Variables and functions */
 int XLC_LAST ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  xlocale_release (scalar_t__) ; 

__attribute__((used)) static void
destruct_locale(void *l)
{
	locale_t loc = l;

	for (int type=0 ; type<XLC_LAST ; type++) {
		if (loc->components[type]) {
			xlocale_release(loc->components[type]);
		}
	}
	if (loc->csym) {
		free(loc->csym);
	}
	free(l);
}