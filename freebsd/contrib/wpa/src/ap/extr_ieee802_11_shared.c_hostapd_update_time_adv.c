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
struct os_tm {int /*<<< orphan*/  sec; int /*<<< orphan*/  min; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  month; int /*<<< orphan*/  year; } ;
struct os_time {int /*<<< orphan*/  sec; } ;
struct hostapd_data {int /*<<< orphan*/  time_update_counter; int /*<<< orphan*/ * time_adv; TYPE_1__* conf; } ;
struct TYPE_2__ {int time_advertisement; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_TIME_ADVERTISEMENT ; 
 int /*<<< orphan*/  WPA_PUT_LE16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ os_get_time (struct os_time*) ; 
 scalar_t__ os_gmtime (int /*<<< orphan*/ ,struct os_tm*) ; 
 int /*<<< orphan*/ * wpabuf_alloc (int const) ; 
 int /*<<< orphan*/ * wpabuf_mhead_u8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpabuf_put (int /*<<< orphan*/ *,int const) ; 

int hostapd_update_time_adv(struct hostapd_data *hapd)
{
	const int elen = 2 + 1 + 10 + 5 + 1;
	struct os_time t;
	struct os_tm tm;
	u8 *pos;

	if (hapd->conf->time_advertisement != 2)
		return 0;

	if (os_get_time(&t) < 0 || os_gmtime(t.sec, &tm) < 0)
		return -1;

	if (!hapd->time_adv) {
		hapd->time_adv = wpabuf_alloc(elen);
		if (hapd->time_adv == NULL)
			return -1;
		pos = wpabuf_put(hapd->time_adv, elen);
	} else
		pos = wpabuf_mhead_u8(hapd->time_adv);

	*pos++ = WLAN_EID_TIME_ADVERTISEMENT;
	*pos++ = 1 + 10 + 5 + 1;

	*pos++ = 2; /* UTC time at which the TSF timer is 0 */

	/* Time Value at TSF 0 */
	/* FIX: need to calculate this based on the current TSF value */
	WPA_PUT_LE16(pos, tm.year); /* Year */
	pos += 2;
	*pos++ = tm.month; /* Month */
	*pos++ = tm.day; /* Day of month */
	*pos++ = tm.hour; /* Hours */
	*pos++ = tm.min; /* Minutes */
	*pos++ = tm.sec; /* Seconds */
	WPA_PUT_LE16(pos, 0); /* Milliseconds (not used) */
	pos += 2;
	*pos++ = 0; /* Reserved */

	/* Time Error */
	/* TODO: fill in an estimate on the error */
	*pos++ = 0;
	*pos++ = 0;
	*pos++ = 0;
	*pos++ = 0;
	*pos++ = 0;

	*pos++ = hapd->time_update_counter++;

	return 0;
}