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
struct sta_info {unsigned int airtime_weight; int /*<<< orphan*/  addr; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int hostapd_sta_set_airtime_weight (struct hostapd_data*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int sta_set_airtime_weight(struct hostapd_data *hapd,
				  struct sta_info *sta,
				  unsigned int weight)
{
	int ret = 0;

	if (weight != sta->airtime_weight &&
	    (ret = hostapd_sta_set_airtime_weight(hapd, sta->addr, weight)))
		return ret;

	sta->airtime_weight = weight;
	return ret;
}