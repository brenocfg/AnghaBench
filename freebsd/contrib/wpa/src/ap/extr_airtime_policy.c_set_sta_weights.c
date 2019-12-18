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
struct sta_info {struct sta_info* next; } ;
struct hostapd_data {struct sta_info* sta_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  sta_set_airtime_weight (struct hostapd_data*,struct sta_info*,unsigned int) ; 

__attribute__((used)) static void set_sta_weights(struct hostapd_data *hapd, unsigned int weight)
{
	struct sta_info *sta;

	for (sta = hapd->sta_list; sta; sta = sta->next)
		sta_set_airtime_weight(hapd, sta, weight);
}