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
struct sta_info {int /*<<< orphan*/  addr; } ;
struct hostapd_data {TYPE_1__* iconf; } ;
struct TYPE_2__ {scalar_t__ airtime_mode; } ;

/* Variables and functions */
 scalar_t__ AIRTIME_MODE_STATIC ; 
 unsigned int get_weight_for_sta (struct hostapd_data*,int /*<<< orphan*/ ) ; 
 int sta_set_airtime_weight (struct hostapd_data*,struct sta_info*,unsigned int) ; 

int airtime_policy_new_sta(struct hostapd_data *hapd, struct sta_info *sta)
{
	unsigned int weight;

	if (hapd->iconf->airtime_mode == AIRTIME_MODE_STATIC) {
		weight = get_weight_for_sta(hapd, sta->addr);
		if (weight)
			return sta_set_airtime_weight(hapd, sta, weight);
	}
	return 0;
}