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
typedef  scalar_t__ u_short ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ bios; } ;

/* Variables and functions */
 int APM_BIOS_DISABLED ; 
 int APM_BIOS_DISENGAGED ; 
 scalar_t__ APM_DEVICE_ALL ; 
 int APM_DISABLED ; 
 int /*<<< orphan*/  APM_FUNC_ENGAGE_PM ; 
 int APM_SUCCESS ; 
 scalar_t__ apm_bios_call_simple (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int*) ; 
 TYPE_2__ apm_info ; 

__attribute__((used)) static int apm_engage_power_management(u_short device, int enable)
{
	u32 eax;
	int err;

	if ((enable == 0) && (device == APM_DEVICE_ALL)
	    && (apm_info.bios.flags & APM_BIOS_DISABLED))
		return APM_DISABLED;
	if (apm_bios_call_simple(APM_FUNC_ENGAGE_PM, device, enable,
				 &eax, &err))
		return err;
	if (device == APM_DEVICE_ALL) {
		if (enable)
			apm_info.bios.flags &= ~APM_BIOS_DISENGAGED;
		else
			apm_info.bios.flags |= APM_BIOS_DISENGAGED;
	}
	return APM_SUCCESS;
}