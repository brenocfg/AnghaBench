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
typedef  int u32 ;
struct wpa_driver_ndis_data {int dummy; } ;
typedef  int /*<<< orphan*/  auth_mode ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  OID_802_11_AUTHENTICATION_MODE ; 
 int ndis_get_oid (struct wpa_driver_ndis_data*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ndis_get_auth_mode(struct wpa_driver_ndis_data *drv)
{
	u32 auth_mode;
	int res;
	res = ndis_get_oid(drv, OID_802_11_AUTHENTICATION_MODE,
			   (char *) &auth_mode, sizeof(auth_mode));
	if (res != sizeof(auth_mode)) {
		wpa_printf(MSG_DEBUG, "NDIS: Failed to get "
			   "OID_802_11_AUTHENTICATION_MODE");
		return -1;
	}
	return auth_mode;
}