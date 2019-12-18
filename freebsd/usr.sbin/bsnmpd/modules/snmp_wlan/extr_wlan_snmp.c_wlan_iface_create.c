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
struct wlan_iface {scalar_t__ state; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  RowStatus_active ; 
 int SNMP_ERR_NOERROR ; 
 scalar_t__ wlanIfaceState_up ; 
 int wlan_clone_create (struct wlan_iface*) ; 
 int /*<<< orphan*/  wlan_config_state (struct wlan_iface*,int) ; 

__attribute__((used)) static int
wlan_iface_create(struct wlan_iface *wif)
{
	int rc;

	if ((rc = wlan_clone_create(wif)) == SNMP_ERR_NOERROR) {
		/*
		 * The rest of the info will be updated once the
		 * snmp_mibII module notifies us of the interface.
		 */
		wif->status = RowStatus_active;
		if (wif->state == wlanIfaceState_up)
			(void)wlan_config_state(wif, 1);
	}

	return (rc);
}