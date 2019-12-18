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
struct hostapd_data {int /*<<< orphan*/ * time_adv; TYPE_1__* conf; } ;
struct TYPE_2__ {int time_advertisement; } ;

/* Variables and functions */
 scalar_t__ hostapd_update_time_adv (struct hostapd_data*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_len (int /*<<< orphan*/ *) ; 

u8 * hostapd_eid_time_adv(struct hostapd_data *hapd, u8 *eid)
{
	if (hapd->conf->time_advertisement != 2)
		return eid;

	if (hapd->time_adv == NULL &&
	    hostapd_update_time_adv(hapd) < 0)
		return eid;

	if (hapd->time_adv == NULL)
		return eid;

	os_memcpy(eid, wpabuf_head(hapd->time_adv),
		  wpabuf_len(hapd->time_adv));
	eid += wpabuf_len(hapd->time_adv);

	return eid;
}