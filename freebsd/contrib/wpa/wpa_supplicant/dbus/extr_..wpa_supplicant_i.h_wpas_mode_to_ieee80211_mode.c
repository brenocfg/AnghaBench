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
typedef  enum wpas_mode { ____Placeholder_wpas_mode } wpas_mode ;

/* Variables and functions */
 int IEEE80211_MODE_AP ; 
 int IEEE80211_MODE_IBSS ; 
 int IEEE80211_MODE_INFRA ; 
 int IEEE80211_MODE_MESH ; 
#define  WPAS_MODE_AP 133 
#define  WPAS_MODE_IBSS 132 
#define  WPAS_MODE_INFRA 131 
#define  WPAS_MODE_MESH 130 
#define  WPAS_MODE_P2P_GO 129 
#define  WPAS_MODE_P2P_GROUP_FORMATION 128 

__attribute__((used)) static inline int wpas_mode_to_ieee80211_mode(enum wpas_mode mode)
{
	switch (mode) {
	default:
	case WPAS_MODE_INFRA:
		return IEEE80211_MODE_INFRA;
	case WPAS_MODE_IBSS:
		return IEEE80211_MODE_IBSS;
	case WPAS_MODE_AP:
	case WPAS_MODE_P2P_GO:
	case WPAS_MODE_P2P_GROUP_FORMATION:
		return IEEE80211_MODE_AP;
	case WPAS_MODE_MESH:
		return IEEE80211_MODE_MESH;
	}
}