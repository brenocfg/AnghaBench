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
struct TYPE_4__ {scalar_t__ charge_mode; TYPE_1__* machinfo; } ;
struct TYPE_3__ {int status_high_acin; int status_low_acin; int status_high_noac; int status_low_noac; } ;

/* Variables and functions */
 int APM_BATTERY_STATUS_CRITICAL ; 
 int APM_BATTERY_STATUS_HIGH ; 
 int APM_BATTERY_STATUS_LOW ; 
 scalar_t__ CHRG_ON ; 
 TYPE_2__ sharpsl_pm ; 

__attribute__((used)) static int get_apm_status(int voltage)
{
	int low_thresh, high_thresh;

	if (sharpsl_pm.charge_mode == CHRG_ON) {
		high_thresh = sharpsl_pm.machinfo->status_high_acin;
		low_thresh = sharpsl_pm.machinfo->status_low_acin;
	} else {
		high_thresh = sharpsl_pm.machinfo->status_high_noac;
		low_thresh = sharpsl_pm.machinfo->status_low_noac;
	}

	if (voltage >= high_thresh)
		return APM_BATTERY_STATUS_HIGH;
	if (voltage >= low_thresh)
		return APM_BATTERY_STATUS_LOW;
	return APM_BATTERY_STATUS_CRITICAL;
}