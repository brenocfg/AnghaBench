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
struct TYPE_2__ {int flags; int /*<<< orphan*/  (* init ) () ;} ;

/* Variables and functions */
 int CAM_PERIPH_DRV_EARLY ; 
 int initialized ; 
 int max (int,int) ; 
 TYPE_1__** periph_drivers ; 
 int /*<<< orphan*/  stub1 () ; 

void
periphdriver_init(int level)
{
	int	i, early;

	initialized = max(initialized, level);
	for (i = 0; periph_drivers[i] != NULL; i++) {
		early = (periph_drivers[i]->flags & CAM_PERIPH_DRV_EARLY) ? 1 : 2;
		if (early == initialized)
			(*periph_drivers[i]->init)();
	}
}