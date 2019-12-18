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
typedef  int u16 ;
struct ieee80211_hdr {int /*<<< orphan*/  const* addr3; int /*<<< orphan*/  const* addr1; int /*<<< orphan*/  const* addr2; int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
#define  WLAN_FC_FROMDS 132 
 int WLAN_FC_GET_STYPE (int) ; 
 int WLAN_FC_GET_TYPE (int) ; 
 int WLAN_FC_STYPE_PSPOLL ; 
#define  WLAN_FC_TODS 131 
#define  WLAN_FC_TYPE_CTRL 130 
#define  WLAN_FC_TYPE_DATA 129 
#define  WLAN_FC_TYPE_MGMT 128 
 int le_to_host16 (int /*<<< orphan*/ ) ; 

const u8 * get_hdr_bssid(const struct ieee80211_hdr *hdr, size_t len)
{
	u16 fc, type, stype;

	/*
	 * PS-Poll frames are 16 bytes. All other frames are
	 * 24 bytes or longer.
	 */
	if (len < 16)
		return NULL;

	fc = le_to_host16(hdr->frame_control);
	type = WLAN_FC_GET_TYPE(fc);
	stype = WLAN_FC_GET_STYPE(fc);

	switch (type) {
	case WLAN_FC_TYPE_DATA:
		if (len < 24)
			return NULL;
		switch (fc & (WLAN_FC_FROMDS | WLAN_FC_TODS)) {
		case WLAN_FC_FROMDS | WLAN_FC_TODS:
		case WLAN_FC_TODS:
			return hdr->addr1;
		case WLAN_FC_FROMDS:
			return hdr->addr2;
		default:
			return NULL;
		}
	case WLAN_FC_TYPE_CTRL:
		if (stype != WLAN_FC_STYPE_PSPOLL)
			return NULL;
		return hdr->addr1;
	case WLAN_FC_TYPE_MGMT:
		return hdr->addr3;
	default:
		return NULL;
	}
}