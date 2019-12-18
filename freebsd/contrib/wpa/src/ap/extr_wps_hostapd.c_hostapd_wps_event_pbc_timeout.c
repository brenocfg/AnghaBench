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
struct TYPE_2__ {int /*<<< orphan*/  pbc_status; } ;
struct hostapd_data {TYPE_1__ wps_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPS_PBC_STATUS_TIMEOUT ; 

__attribute__((used)) static void hostapd_wps_event_pbc_timeout(struct hostapd_data *hapd)
{
	/* Update WPS PBC Status:PBC Timeout */
	hapd->wps_stats.pbc_status = WPS_PBC_STATUS_TIMEOUT;
}