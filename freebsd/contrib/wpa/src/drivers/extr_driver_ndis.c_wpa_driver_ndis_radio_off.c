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
struct wpa_driver_ndis_data {scalar_t__ radio_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  OID_802_11_DISASSOCIATE ; 
 int ndis_set_oid (struct wpa_driver_ndis_data*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int wpa_driver_ndis_radio_off(struct wpa_driver_ndis_data *drv)
{
	drv->radio_enabled = 0;
	return ndis_set_oid(drv, OID_802_11_DISASSOCIATE, "    ", 4);
}