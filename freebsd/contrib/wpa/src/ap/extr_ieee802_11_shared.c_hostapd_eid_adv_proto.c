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
struct TYPE_2__ {int /*<<< orphan*/  interworking; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_NETWORK_QUERY_PROTOCOL ; 
 int /*<<< orphan*/  WLAN_EID_ADV_PROTO ; 

u8 * hostapd_eid_adv_proto(struct hostapd_data *hapd, u8 *eid)
{
	u8 *pos = eid;
#ifdef CONFIG_INTERWORKING

	/* TODO: Separate configuration for ANQP? */
	if (!hapd->conf->interworking)
		return eid;

	*pos++ = WLAN_EID_ADV_PROTO;
	*pos++ = 2;
	*pos++ = 0x7F; /* Query Response Length Limit | PAME-BI */
	*pos++ = ACCESS_NETWORK_QUERY_PROTOCOL;
#endif /* CONFIG_INTERWORKING */

	return pos;
}