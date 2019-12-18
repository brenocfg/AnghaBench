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
struct TYPE_2__ {int time_advertisement; int /*<<< orphan*/  time_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_TIME_ZONE ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 size_t os_strlen (int /*<<< orphan*/ ) ; 

u8 * hostapd_eid_time_zone(struct hostapd_data *hapd, u8 *eid)
{
	size_t len;

	if (hapd->conf->time_advertisement != 2 || !hapd->conf->time_zone)
		return eid;

	len = os_strlen(hapd->conf->time_zone);

	*eid++ = WLAN_EID_TIME_ZONE;
	*eid++ = len;
	os_memcpy(eid, hapd->conf->time_zone, len);
	eid += len;

	return eid;
}