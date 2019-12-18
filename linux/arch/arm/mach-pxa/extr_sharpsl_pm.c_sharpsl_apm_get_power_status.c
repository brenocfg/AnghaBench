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
struct apm_power_info {int battery_status; int battery_flag; int /*<<< orphan*/  battery_life; int /*<<< orphan*/  ac_line_status; } ;
struct TYPE_3__ {int mainbat_status; int /*<<< orphan*/  mainbat_percent; int /*<<< orphan*/  ac_status; } ;
struct TYPE_4__ {scalar_t__ charge_mode; TYPE_1__ battstat; } ;

/* Variables and functions */
 int APM_BATTERY_STATUS_CHARGING ; 
 scalar_t__ CHRG_ON ; 
 TYPE_2__ sharpsl_pm ; 

__attribute__((used)) static void sharpsl_apm_get_power_status(struct apm_power_info *info)
{
	info->ac_line_status = sharpsl_pm.battstat.ac_status;

	if (sharpsl_pm.charge_mode == CHRG_ON)
		info->battery_status = APM_BATTERY_STATUS_CHARGING;
	else
		info->battery_status = sharpsl_pm.battstat.mainbat_status;

	info->battery_flag = (1 << info->battery_status);
	info->battery_life = sharpsl_pm.battstat.mainbat_percent;
}