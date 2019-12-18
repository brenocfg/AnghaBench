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

/* Variables and functions */
#define  WPA_KEY_MGMT_DPP 149 
#define  WPA_KEY_MGMT_FILS_SHA256 148 
#define  WPA_KEY_MGMT_FILS_SHA384 147 
#define  WPA_KEY_MGMT_FT_FILS_SHA256 146 
#define  WPA_KEY_MGMT_FT_FILS_SHA384 145 
#define  WPA_KEY_MGMT_FT_IEEE8021X 144 
#define  WPA_KEY_MGMT_FT_IEEE8021X_SHA384 143 
#define  WPA_KEY_MGMT_FT_PSK 142 
#define  WPA_KEY_MGMT_FT_SAE 141 
#define  WPA_KEY_MGMT_IEEE8021X 140 
#define  WPA_KEY_MGMT_IEEE8021X_NO_WPA 139 
#define  WPA_KEY_MGMT_IEEE8021X_SHA256 138 
#define  WPA_KEY_MGMT_IEEE8021X_SUITE_B 137 
#define  WPA_KEY_MGMT_IEEE8021X_SUITE_B_192 136 
#define  WPA_KEY_MGMT_NONE 135 
#define  WPA_KEY_MGMT_OSEN 134 
#define  WPA_KEY_MGMT_OWE 133 
#define  WPA_KEY_MGMT_PSK 132 
#define  WPA_KEY_MGMT_PSK_SHA256 131 
#define  WPA_KEY_MGMT_SAE 130 
#define  WPA_KEY_MGMT_WPA_NONE 129 
#define  WPA_KEY_MGMT_WPS 128 
 int WPA_PROTO_RSN ; 
 int WPA_PROTO_WPA ; 

const char * wpa_key_mgmt_txt(int key_mgmt, int proto)
{
	switch (key_mgmt) {
	case WPA_KEY_MGMT_IEEE8021X:
		if (proto == (WPA_PROTO_RSN | WPA_PROTO_WPA))
			return "WPA2+WPA/IEEE 802.1X/EAP";
		return proto == WPA_PROTO_RSN ?
			"WPA2/IEEE 802.1X/EAP" : "WPA/IEEE 802.1X/EAP";
	case WPA_KEY_MGMT_PSK:
		if (proto == (WPA_PROTO_RSN | WPA_PROTO_WPA))
			return "WPA2-PSK+WPA-PSK";
		return proto == WPA_PROTO_RSN ?
			"WPA2-PSK" : "WPA-PSK";
	case WPA_KEY_MGMT_NONE:
		return "NONE";
	case WPA_KEY_MGMT_WPA_NONE:
		return "WPA-NONE";
	case WPA_KEY_MGMT_IEEE8021X_NO_WPA:
		return "IEEE 802.1X (no WPA)";
#ifdef CONFIG_IEEE80211R
	case WPA_KEY_MGMT_FT_IEEE8021X:
		return "FT-EAP";
	case WPA_KEY_MGMT_FT_IEEE8021X_SHA384:
		return "FT-EAP-SHA384";
	case WPA_KEY_MGMT_FT_PSK:
		return "FT-PSK";
#endif /* CONFIG_IEEE80211R */
#ifdef CONFIG_IEEE80211W
	case WPA_KEY_MGMT_IEEE8021X_SHA256:
		return "WPA2-EAP-SHA256";
	case WPA_KEY_MGMT_PSK_SHA256:
		return "WPA2-PSK-SHA256";
#endif /* CONFIG_IEEE80211W */
	case WPA_KEY_MGMT_WPS:
		return "WPS";
	case WPA_KEY_MGMT_SAE:
		return "SAE";
	case WPA_KEY_MGMT_FT_SAE:
		return "FT-SAE";
	case WPA_KEY_MGMT_OSEN:
		return "OSEN";
	case WPA_KEY_MGMT_IEEE8021X_SUITE_B:
		return "WPA2-EAP-SUITE-B";
	case WPA_KEY_MGMT_IEEE8021X_SUITE_B_192:
		return "WPA2-EAP-SUITE-B-192";
	case WPA_KEY_MGMT_FILS_SHA256:
		return "FILS-SHA256";
	case WPA_KEY_MGMT_FILS_SHA384:
		return "FILS-SHA384";
	case WPA_KEY_MGMT_FT_FILS_SHA256:
		return "FT-FILS-SHA256";
	case WPA_KEY_MGMT_FT_FILS_SHA384:
		return "FT-FILS-SHA384";
	case WPA_KEY_MGMT_OWE:
		return "OWE";
	case WPA_KEY_MGMT_DPP:
		return "DPP";
	default:
		return "UNKNOWN";
	}
}