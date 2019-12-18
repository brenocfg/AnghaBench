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
typedef  enum phy_type { ____Placeholder_phy_type } phy_type ;
typedef  enum hostapd_hw_mode { ____Placeholder_hostapd_hw_mode } hostapd_hw_mode ;

/* Variables and functions */
#define  HOSTAPD_MODE_IEEE80211A 131 
#define  HOSTAPD_MODE_IEEE80211AD 130 
#define  HOSTAPD_MODE_IEEE80211B 129 
#define  HOSTAPD_MODE_IEEE80211G 128 
 int PHY_TYPE_DMG ; 
 int PHY_TYPE_ERP ; 
 int PHY_TYPE_HRDSSS ; 
 int PHY_TYPE_OFDM ; 
 int PHY_TYPE_UNSPECIFIED ; 
 int ieee80211_freq_to_chan (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum phy_type ieee80211_phy_type_by_freq(int freq)
{
	enum hostapd_hw_mode hw_mode;
	u8 channel;

	hw_mode = ieee80211_freq_to_chan(freq, &channel);

	switch (hw_mode) {
	case HOSTAPD_MODE_IEEE80211A:
		return PHY_TYPE_OFDM;
	case HOSTAPD_MODE_IEEE80211B:
		return PHY_TYPE_HRDSSS;
	case HOSTAPD_MODE_IEEE80211G:
		return PHY_TYPE_ERP;
	case HOSTAPD_MODE_IEEE80211AD:
		return PHY_TYPE_DMG;
	default:
		return PHY_TYPE_UNSPECIFIED;
	};
}