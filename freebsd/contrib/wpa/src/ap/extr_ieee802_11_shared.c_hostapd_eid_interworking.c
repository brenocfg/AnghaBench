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
typedef  int u8 ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {int access_network_type; int /*<<< orphan*/  hessid; int /*<<< orphan*/  venue_type; int /*<<< orphan*/  venue_group; scalar_t__ venue_info_set; scalar_t__ uesa; scalar_t__ esr; scalar_t__ asra; scalar_t__ internet; int /*<<< orphan*/  interworking; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int INTERWORKING_ANO_ASRA ; 
 int INTERWORKING_ANO_ESR ; 
 int INTERWORKING_ANO_INTERNET ; 
 int INTERWORKING_ANO_UESA ; 
 int /*<<< orphan*/  WLAN_EID_INTERWORKING ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8 * hostapd_eid_interworking(struct hostapd_data *hapd, u8 *eid)
{
	u8 *pos = eid;
#ifdef CONFIG_INTERWORKING
	u8 *len;

	if (!hapd->conf->interworking)
		return eid;

	*pos++ = WLAN_EID_INTERWORKING;
	len = pos++;

	*pos = hapd->conf->access_network_type;
	if (hapd->conf->internet)
		*pos |= INTERWORKING_ANO_INTERNET;
	if (hapd->conf->asra)
		*pos |= INTERWORKING_ANO_ASRA;
	if (hapd->conf->esr)
		*pos |= INTERWORKING_ANO_ESR;
	if (hapd->conf->uesa)
		*pos |= INTERWORKING_ANO_UESA;
	pos++;

	if (hapd->conf->venue_info_set) {
		*pos++ = hapd->conf->venue_group;
		*pos++ = hapd->conf->venue_type;
	}

	if (!is_zero_ether_addr(hapd->conf->hessid)) {
		os_memcpy(pos, hapd->conf->hessid, ETH_ALEN);
		pos += ETH_ALEN;
	}

	*len = pos - len - 1;
#endif /* CONFIG_INTERWORKING */

	return pos;
}