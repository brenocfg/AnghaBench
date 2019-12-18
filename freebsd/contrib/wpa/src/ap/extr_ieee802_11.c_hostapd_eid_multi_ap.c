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
typedef  int /*<<< orphan*/  u8 ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {int multi_ap; } ;

/* Variables and functions */
 int BACKHAUL_BSS ; 
 int FRONTHAUL_BSS ; 
 int /*<<< orphan*/  MULTI_AP_BACKHAUL_BSS ; 
 int /*<<< orphan*/  MULTI_AP_FRONTHAUL_BSS ; 
 int add_multi_ap_ie (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

u8 * hostapd_eid_multi_ap(struct hostapd_data *hapd, u8 *eid)
{
	u8 multi_ap_val = 0;

	if (!hapd->conf->multi_ap)
		return eid;
	if (hapd->conf->multi_ap & BACKHAUL_BSS)
		multi_ap_val |= MULTI_AP_BACKHAUL_BSS;
	if (hapd->conf->multi_ap & FRONTHAUL_BSS)
		multi_ap_val |= MULTI_AP_FRONTHAUL_BSS;

	return eid + add_multi_ap_ie(eid, 9, multi_ap_val);
}