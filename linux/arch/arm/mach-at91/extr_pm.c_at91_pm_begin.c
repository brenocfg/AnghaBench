#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int suspend_state_t ;
struct TYPE_3__ {int mode; int suspend_mode; int standby_mode; } ;
struct TYPE_4__ {TYPE_1__ data; } ;

/* Variables and functions */
#define  PM_SUSPEND_MEM 129 
#define  PM_SUSPEND_STANDBY 128 
 int at91_pm_config_ws (int,int) ; 
 TYPE_2__ soc_pm ; 

__attribute__((used)) static int at91_pm_begin(suspend_state_t state)
{
	switch (state) {
	case PM_SUSPEND_MEM:
		soc_pm.data.mode = soc_pm.data.suspend_mode;
		break;

	case PM_SUSPEND_STANDBY:
		soc_pm.data.mode = soc_pm.data.standby_mode;
		break;

	default:
		soc_pm.data.mode = -1;
	}

	return at91_pm_config_ws(soc_pm.data.mode, true);
}