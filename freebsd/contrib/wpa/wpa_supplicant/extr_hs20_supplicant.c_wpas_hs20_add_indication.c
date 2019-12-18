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
typedef  int u8 ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int HS20_INDICATION_OUI_TYPE ; 
 int HS20_PPS_MO_ID_PRESENT ; 
 int HS20_VERSION ; 
 int /*<<< orphan*/  OUI_WFA ; 
 int WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  wpabuf_put_be24 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

void wpas_hs20_add_indication(struct wpabuf *buf, int pps_mo_id, int ap_release)
{
	int release;
	u8 conf;

	release = (HS20_VERSION >> 4) + 1;
	if (ap_release > 0 && release > ap_release)
		release = ap_release;
	if (release < 2)
		pps_mo_id = -1;

	wpabuf_put_u8(buf, WLAN_EID_VENDOR_SPECIFIC);
	wpabuf_put_u8(buf, pps_mo_id >= 0 ? 7 : 5);
	wpabuf_put_be24(buf, OUI_WFA);
	wpabuf_put_u8(buf, HS20_INDICATION_OUI_TYPE);
	conf = (release - 1) << 4;
	if (pps_mo_id >= 0)
		conf |= HS20_PPS_MO_ID_PRESENT;
	wpabuf_put_u8(buf, conf);
	if (pps_mo_id >= 0)
		wpabuf_put_le16(buf, pps_mo_id);
}