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
typedef  int /*<<< orphan*/  wps ;
typedef  int /*<<< orphan*/  vhttxmcs ;
typedef  int /*<<< orphan*/  vhtrxmcs ;
typedef  int /*<<< orphan*/  vhtcap ;
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  txpow ;
struct wpabuf {int dummy; } ;
typedef  int /*<<< orphan*/  model_name ;
typedef  int /*<<< orphan*/  htmcs ;
typedef  int /*<<< orphan*/  htcap ;
typedef  int /*<<< orphan*/  htagg ;
typedef  int /*<<< orphan*/  extcap ;

/* Variables and functions */
 int MAX_EXTCAP ; 
 size_t WLAN_EID_EXT_CAPAB ; 
 size_t WLAN_EID_HT_CAP ; 
 size_t WLAN_EID_PWR_CAPABILITY ; 
 size_t WLAN_EID_VENDOR_SPECIFIC ; 
 size_t WLAN_EID_VHT_CAP ; 
 scalar_t__ WPA_GET_BE32 (size_t const*) ; 
 int /*<<< orphan*/  WPA_GET_LE16 (size_t const*) ; 
 scalar_t__ WPA_GET_LE32 (size_t const*) ; 
 scalar_t__ WPS_IE_VENDOR_TYPE ; 
 int /*<<< orphan*/  WPS_NAME_LEN ; 
 scalar_t__ get_wps_name (char*,int /*<<< orphan*/ ,size_t const*,size_t) ; 
 int /*<<< orphan*/  os_memset (char*,int /*<<< orphan*/ ,int) ; 
 int os_snprintf (char*,int,char*,...) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 int os_strlen (char*) ; 
 size_t* wpabuf_head (struct wpabuf const*) ; 
 size_t wpabuf_len (struct wpabuf const*) ; 

__attribute__((used)) static void ie_to_string(char *fstr, size_t fstr_len, const struct wpabuf *ies)
{
	char *fpos = fstr;
	char *fend = fstr + fstr_len;
	char htcap[7 + 4 + 1]; /* ",htcap:" + %04hx + trailing NUL */
	char htagg[7 + 2 + 1]; /* ",htagg:" + %02hx + trailing NUL */
	char htmcs[7 + 8 + 1]; /* ",htmcs:" + %08x + trailing NUL */
	char vhtcap[8 + 8 + 1]; /* ",vhtcap:" + %08x + trailing NUL */
	char vhtrxmcs[10 + 8 + 1]; /* ",vhtrxmcs:" + %08x + trailing NUL */
	char vhttxmcs[10 + 8 + 1]; /* ",vhttxmcs:" + %08x + trailing NUL */
#define MAX_EXTCAP	254
	char extcap[8 + 2 * MAX_EXTCAP + 1]; /* ",extcap:" + hex + trailing NUL
					      */
	char txpow[7 + 4 + 1]; /* ",txpow:" + %04hx + trailing NUL */
#define WPS_NAME_LEN		32
	char wps[WPS_NAME_LEN + 5 + 1]; /* room to prepend ",wps:" + trailing
					 * NUL */
	int num = 0;
	const u8 *ie;
	size_t ie_len;
	int ret;

	os_memset(htcap, 0, sizeof(htcap));
	os_memset(htagg, 0, sizeof(htagg));
	os_memset(htmcs, 0, sizeof(htmcs));
	os_memset(vhtcap, 0, sizeof(vhtcap));
	os_memset(vhtrxmcs, 0, sizeof(vhtrxmcs));
	os_memset(vhttxmcs, 0, sizeof(vhttxmcs));
	os_memset(extcap, 0, sizeof(extcap));
	os_memset(txpow, 0, sizeof(txpow));
	os_memset(wps, 0, sizeof(wps));
	*fpos = '\0';

	if (!ies)
		return;
	ie = wpabuf_head(ies);
	ie_len = wpabuf_len(ies);

	while (ie_len >= 2) {
		u8 id, elen;
		char *sep = (num++ == 0) ? "" : ",";

		id = *ie++;
		elen = *ie++;
		ie_len -= 2;

		if (elen > ie_len)
			break;

		if (id == WLAN_EID_VENDOR_SPECIFIC && elen >= 4) {
			/* Vendor specific */
			if (WPA_GET_BE32(ie) == WPS_IE_VENDOR_TYPE) {
				/* WPS */
				char model_name[WPS_NAME_LEN + 1];
				const u8 *data = &ie[4];
				size_t data_len = elen - 4;

				os_memset(model_name, 0, sizeof(model_name));
				if (get_wps_name(model_name, WPS_NAME_LEN, data,
						 data_len)) {
					os_snprintf(wps, sizeof(wps),
						    ",wps:%s", model_name);
				}
			}

			ret = os_snprintf(fpos, fend - fpos,
					  "%s%d(%02x%02x%02x,%d)",
					  sep, id, ie[0], ie[1], ie[2], ie[3]);
		} else {
			if (id == WLAN_EID_HT_CAP && elen >= 2) {
				/* HT Capabilities (802.11n) */
				os_snprintf(htcap, sizeof(htcap),
					    ",htcap:%04hx",
					    WPA_GET_LE16(ie));
			}
			if (id == WLAN_EID_HT_CAP && elen >= 3) {
				/* HT Capabilities (802.11n), A-MPDU information
				 */
				os_snprintf(htagg, sizeof(htagg),
					    ",htagg:%02hx", (u16) ie[2]);
			}
			if (id == WLAN_EID_HT_CAP && elen >= 7) {
				/* HT Capabilities (802.11n), MCS information */
				os_snprintf(htmcs, sizeof(htmcs),
					    ",htmcs:%08hx",
					    (u16) WPA_GET_LE32(ie + 3));
			}
			if (id == WLAN_EID_VHT_CAP && elen >= 4) {
				/* VHT Capabilities (802.11ac) */
				os_snprintf(vhtcap, sizeof(vhtcap),
					    ",vhtcap:%08x",
					    WPA_GET_LE32(ie));
			}
			if (id == WLAN_EID_VHT_CAP && elen >= 8) {
				/* VHT Capabilities (802.11ac), RX MCS
				 * information */
				os_snprintf(vhtrxmcs, sizeof(vhtrxmcs),
					    ",vhtrxmcs:%08x",
					    WPA_GET_LE32(ie + 4));
			}
			if (id == WLAN_EID_VHT_CAP && elen >= 12) {
				/* VHT Capabilities (802.11ac), TX MCS
				 * information */
				os_snprintf(vhttxmcs, sizeof(vhttxmcs),
					    ",vhttxmcs:%08x",
					    WPA_GET_LE32(ie + 8));
			}
			if (id == WLAN_EID_EXT_CAPAB) {
				/* Extended Capabilities */
				int i;
				int len = (elen < MAX_EXTCAP) ? elen :
					MAX_EXTCAP;
				char *p = extcap;

				p += os_snprintf(extcap, sizeof(extcap),
						 ",extcap:");
				for (i = 0; i < len; i++) {
					int lim;

					lim = sizeof(extcap) -
						os_strlen(extcap);
					if (lim <= 0)
						break;
					p += os_snprintf(p, lim, "%02x",
							 *(ie + i));
				}
			}
			if (id == WLAN_EID_PWR_CAPABILITY && elen == 2) {
				/* TX Power */
				os_snprintf(txpow, sizeof(txpow),
					    ",txpow:%04hx",
					    WPA_GET_LE16(ie));
			}

			ret = os_snprintf(fpos, fend - fpos, "%s%d", sep, id);
		}
		if (os_snprintf_error(fend - fpos, ret))
			goto fail;
		fpos += ret;

		ie += elen;
		ie_len -= elen;
	}

	ret = os_snprintf(fpos, fend - fpos, "%s%s%s%s%s%s%s%s%s",
			  htcap, htagg, htmcs, vhtcap, vhtrxmcs, vhttxmcs,
			  txpow, extcap, wps);
	if (os_snprintf_error(fend - fpos, ret)) {
	fail:
		fstr[0] = '\0';
	}
}