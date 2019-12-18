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
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {int flags; struct sta_info* next; } ;
struct hostapd_data {struct sta_info* sta_list; } ;

/* Variables and functions */
 int WLAN_STA_AUTHORIZED ; 
 int /*<<< orphan*/  x_snoop_mcast_to_ucast_convert_send (struct hostapd_data*,struct sta_info*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void ucast_to_stas(struct hostapd_data *hapd, const u8 *buf, size_t len)
{
	struct sta_info *sta;

	for (sta = hapd->sta_list; sta; sta = sta->next) {
		if (!(sta->flags & WLAN_STA_AUTHORIZED))
			continue;
		x_snoop_mcast_to_ucast_convert_send(hapd, sta, (u8 *) buf, len);
	}
}