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
typedef  enum hostapd_iface_state { ____Placeholder_hostapd_iface_state } hostapd_iface_state ;

/* Variables and functions */
#define  HAPD_IFACE_ACS 134 
#define  HAPD_IFACE_COUNTRY_UPDATE 133 
#define  HAPD_IFACE_DFS 132 
#define  HAPD_IFACE_DISABLED 131 
#define  HAPD_IFACE_ENABLED 130 
#define  HAPD_IFACE_HT_SCAN 129 
#define  HAPD_IFACE_UNINITIALIZED 128 

const char * hostapd_state_text(enum hostapd_iface_state s)
{
	switch (s) {
	case HAPD_IFACE_UNINITIALIZED:
		return "UNINITIALIZED";
	case HAPD_IFACE_DISABLED:
		return "DISABLED";
	case HAPD_IFACE_COUNTRY_UPDATE:
		return "COUNTRY_UPDATE";
	case HAPD_IFACE_ACS:
		return "ACS";
	case HAPD_IFACE_HT_SCAN:
		return "HT_SCAN";
	case HAPD_IFACE_DFS:
		return "DFS";
	case HAPD_IFACE_ENABLED:
		return "ENABLED";
	}

	return "UNKNOWN";
}