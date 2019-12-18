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
struct wpa_driver_ndis_data {scalar_t__ wired; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int SsidLength; int /*<<< orphan*/  Ssid; } ;
typedef  TYPE_1__ NDIS_802_11_SSID ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  OID_802_11_SSID ; 
 int ndis_get_oid (struct wpa_driver_ndis_data*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wpa_driver_ndis_get_ssid(void *priv, u8 *ssid)
{
	struct wpa_driver_ndis_data *drv = priv;
	NDIS_802_11_SSID buf;
	int res;

	res = ndis_get_oid(drv, OID_802_11_SSID, (char *) &buf, sizeof(buf));
	if (res < 4) {
		wpa_printf(MSG_DEBUG, "NDIS: Failed to get SSID");
		if (drv->wired) {
			wpa_printf(MSG_DEBUG, "NDIS: Allow get_ssid failure "
				   "with a wired interface");
			return 0;
		}
		return -1;
	}
	os_memcpy(ssid, buf.Ssid, buf.SsidLength);
	return buf.SsidLength;
}