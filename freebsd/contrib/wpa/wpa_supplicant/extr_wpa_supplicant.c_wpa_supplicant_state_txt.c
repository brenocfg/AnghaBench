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
typedef  enum wpa_states { ____Placeholder_wpa_states } wpa_states ;

/* Variables and functions */
#define  WPA_4WAY_HANDSHAKE 137 
#define  WPA_ASSOCIATED 136 
#define  WPA_ASSOCIATING 135 
#define  WPA_AUTHENTICATING 134 
#define  WPA_COMPLETED 133 
#define  WPA_DISCONNECTED 132 
#define  WPA_GROUP_HANDSHAKE 131 
#define  WPA_INACTIVE 130 
#define  WPA_INTERFACE_DISABLED 129 
#define  WPA_SCANNING 128 

const char * wpa_supplicant_state_txt(enum wpa_states state)
{
	switch (state) {
	case WPA_DISCONNECTED:
		return "DISCONNECTED";
	case WPA_INACTIVE:
		return "INACTIVE";
	case WPA_INTERFACE_DISABLED:
		return "INTERFACE_DISABLED";
	case WPA_SCANNING:
		return "SCANNING";
	case WPA_AUTHENTICATING:
		return "AUTHENTICATING";
	case WPA_ASSOCIATING:
		return "ASSOCIATING";
	case WPA_ASSOCIATED:
		return "ASSOCIATED";
	case WPA_4WAY_HANDSHAKE:
		return "4WAY_HANDSHAKE";
	case WPA_GROUP_HANDSHAKE:
		return "GROUP_HANDSHAKE";
	case WPA_COMPLETED:
		return "COMPLETED";
	default:
		return "UNKNOWN";
	}
}