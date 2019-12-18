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
struct sta_info {int dummy; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sta_ip6addr_del (struct hostapd_data*,struct sta_info*) ; 

void ap_sta_ip6addr_del(struct hostapd_data *hapd, struct sta_info *sta)
{
	sta_ip6addr_del(hapd, sta);
}