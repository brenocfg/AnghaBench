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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct multi_band_ie {size_t len; int band_id; int /*<<< orphan*/  mb_ctrl; int /*<<< orphan*/  fst_session_tmout; int /*<<< orphan*/  chan; scalar_t__ op_class; struct multi_band_ie* bssid; scalar_t__ mb_connection_capability; int /*<<< orphan*/  eid; } ;
typedef  enum mb_band_id { ____Placeholder_mb_band_id } mb_band_id ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 int /*<<< orphan*/  FST_DEFAULT_SESSION_TIMEOUT_TU ; 
 scalar_t__ MB_CONNECTION_CAPABILITY_AP ; 
 int /*<<< orphan*/  MB_CTRL_STA_MAC_PRESENT ; 
 int /*<<< orphan*/  MB_STA_ROLE_AP ; 
 int /*<<< orphan*/  MB_STA_ROLE_NON_PCP_NON_AP ; 
 int /*<<< orphan*/  WLAN_EID_MULTI_BAND ; 
 int /*<<< orphan*/  os_memcpy (struct multi_band_ie*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  os_memset (struct multi_band_ie*,int /*<<< orphan*/ ,size_t) ; 
 struct multi_band_ie* wpabuf_put (struct wpabuf*,size_t) ; 

__attribute__((used)) static void fst_fill_mb_ie(struct wpabuf *buf, const u8 *bssid,
			   const u8 *own_addr, enum mb_band_id band, u8 channel)
{
	struct multi_band_ie *mbie;
	size_t len = sizeof(*mbie);

	if (own_addr)
		len += ETH_ALEN;

	mbie = wpabuf_put(buf, len);

	os_memset(mbie, 0, len);

	mbie->eid = WLAN_EID_MULTI_BAND;
	mbie->len = len - 2;
#ifdef HOSTAPD
	mbie->mb_ctrl = MB_STA_ROLE_AP;
	mbie->mb_connection_capability = MB_CONNECTION_CAPABILITY_AP;
#else /* HOSTAPD */
	mbie->mb_ctrl = MB_STA_ROLE_NON_PCP_NON_AP;
	mbie->mb_connection_capability = 0;
#endif /* HOSTAPD */
	if (bssid)
		os_memcpy(mbie->bssid, bssid, ETH_ALEN);
	mbie->band_id = band;
	mbie->op_class = 0;  /* means all */
	mbie->chan = channel;
	mbie->fst_session_tmout = FST_DEFAULT_SESSION_TIMEOUT_TU;

	if (own_addr) {
		mbie->mb_ctrl |= MB_CTRL_STA_MAC_PRESENT;
		os_memcpy(&mbie[1], own_addr, ETH_ALEN);
	}
}