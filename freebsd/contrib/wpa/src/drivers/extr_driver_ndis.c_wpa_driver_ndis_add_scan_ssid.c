#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpa_scan_res {int ie_len; } ;
struct TYPE_3__ {int SsidLength; int /*<<< orphan*/  Ssid; } ;
typedef  TYPE_1__ NDIS_802_11_SSID ;

/* Variables and functions */
 int SSID_MAX_LEN ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct wpa_scan_res* os_realloc (struct wpa_scan_res*,int) ; 
 scalar_t__ wpa_scan_get_ie (struct wpa_scan_res*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpa_scan_res * wpa_driver_ndis_add_scan_ssid(
	struct wpa_scan_res *r, NDIS_802_11_SSID *ssid)
{
	struct wpa_scan_res *nr;
	u8 *pos;

	if (wpa_scan_get_ie(r, WLAN_EID_SSID))
		return r; /* SSID IE already present */

	if (ssid->SsidLength == 0 || ssid->SsidLength > SSID_MAX_LEN)
		return r; /* No valid SSID inside scan data */

	nr = os_realloc(r, sizeof(*r) + r->ie_len + 2 + ssid->SsidLength);
	if (nr == NULL)
		return r;

	pos = ((u8 *) (nr + 1)) + nr->ie_len;
	*pos++ = WLAN_EID_SSID;
	*pos++ = ssid->SsidLength;
	os_memcpy(pos, ssid->Ssid, ssid->SsidLength);
	nr->ie_len += 2 + ssid->SsidLength;

	return nr;
}