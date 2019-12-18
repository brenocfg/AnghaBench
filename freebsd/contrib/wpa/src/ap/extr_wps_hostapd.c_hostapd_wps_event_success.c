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
struct wps_event_success {int /*<<< orphan*/  peer_macaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  status; int /*<<< orphan*/  pbc_status; } ;
struct hostapd_data {TYPE_1__ wps_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  WPS_PBC_STATUS_DISABLE ; 
 int /*<<< orphan*/  WPS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostapd_wps_event_success(struct hostapd_data *hapd,
				      struct wps_event_success *success)
{
	/* Update WPS status - Success */
	hapd->wps_stats.pbc_status = WPS_PBC_STATUS_DISABLE;
	hapd->wps_stats.status = WPS_STATUS_SUCCESS;
	os_memcpy(hapd->wps_stats.peer_addr, success->peer_macaddr, ETH_ALEN);
}