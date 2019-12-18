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
typedef  int u8 ;
struct hostapd_data {TYPE_2__* conf; } ;
struct TYPE_4__ {int roaming_consortium_count; TYPE_1__* roaming_consortium; int /*<<< orphan*/  interworking; } ;
struct TYPE_3__ {int len; int /*<<< orphan*/  oi; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_ROAMING_CONSORTIUM ; 
 int /*<<< orphan*/  os_memcpy (int*,int /*<<< orphan*/ ,int) ; 

u8 * hostapd_eid_roaming_consortium(struct hostapd_data *hapd, u8 *eid)
{
	u8 *pos = eid;
#ifdef CONFIG_INTERWORKING
	u8 *len;
	unsigned int i, count;

	if (!hapd->conf->interworking ||
	    hapd->conf->roaming_consortium == NULL ||
	    hapd->conf->roaming_consortium_count == 0)
		return eid;

	*pos++ = WLAN_EID_ROAMING_CONSORTIUM;
	len = pos++;

	/* Number of ANQP OIs (in addition to the max 3 listed here) */
	if (hapd->conf->roaming_consortium_count > 3 + 255)
		*pos++ = 255;
	else if (hapd->conf->roaming_consortium_count > 3)
		*pos++ = hapd->conf->roaming_consortium_count - 3;
	else
		*pos++ = 0;

	/* OU #1 and #2 Lengths */
	*pos = hapd->conf->roaming_consortium[0].len;
	if (hapd->conf->roaming_consortium_count > 1)
		*pos |= hapd->conf->roaming_consortium[1].len << 4;
	pos++;

	if (hapd->conf->roaming_consortium_count > 3)
		count = 3;
	else
		count = hapd->conf->roaming_consortium_count;

	for (i = 0; i < count; i++) {
		os_memcpy(pos, hapd->conf->roaming_consortium[i].oi,
			  hapd->conf->roaming_consortium[i].len);
		pos += hapd->conf->roaming_consortium[i].len;
	}

	*len = pos - len - 1;
#endif /* CONFIG_INTERWORKING */

	return pos;
}