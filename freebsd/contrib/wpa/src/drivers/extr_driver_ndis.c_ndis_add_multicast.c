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
struct wpa_driver_ndis_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  OID_802_3_MULTICAST_LIST ; 
 scalar_t__ ndis_set_oid (struct wpa_driver_ndis_data*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ pae_group_addr ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ndis_add_multicast(struct wpa_driver_ndis_data *drv)
{
	if (ndis_set_oid(drv, OID_802_3_MULTICAST_LIST,
			 (const char *) pae_group_addr, ETH_ALEN) < 0) {
		wpa_printf(MSG_DEBUG, "NDIS: Failed to add PAE group address "
			   "to the multicast list");
		return -1;
	}

	return 0;
}