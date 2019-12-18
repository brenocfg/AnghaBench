#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_5__ {int expires; } ;

/* Variables and functions */
#define  APPLDATA_ADD_TIMER 130 
#define  APPLDATA_DEL_TIMER 129 
#define  APPLDATA_MOD_TIMER 128 
 int TOD_MICRO ; 
 int /*<<< orphan*/  add_virt_timer_periodic (TYPE_1__*) ; 
 scalar_t__ appldata_interval ; 
 TYPE_1__ appldata_timer ; 
 int appldata_timer_active ; 
 int /*<<< orphan*/  del_virt_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  mod_virt_timer_periodic (TYPE_1__*,int) ; 

__attribute__((used)) static void __appldata_vtimer_setup(int cmd)
{
	u64 timer_interval = (u64) appldata_interval * 1000 * TOD_MICRO;

	switch (cmd) {
	case APPLDATA_ADD_TIMER:
		if (appldata_timer_active)
			break;
		appldata_timer.expires = timer_interval;
		add_virt_timer_periodic(&appldata_timer);
		appldata_timer_active = 1;
		break;
	case APPLDATA_DEL_TIMER:
		del_virt_timer(&appldata_timer);
		if (!appldata_timer_active)
			break;
		appldata_timer_active = 0;
		break;
	case APPLDATA_MOD_TIMER:
		if (!appldata_timer_active)
			break;
		mod_virt_timer_periodic(&appldata_timer, timer_interval);
	}
}