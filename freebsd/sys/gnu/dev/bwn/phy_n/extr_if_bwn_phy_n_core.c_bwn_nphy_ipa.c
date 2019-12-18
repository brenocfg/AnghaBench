#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* phy_n; } ;
struct bwn_mac {TYPE_2__ mac_phy; } ;
typedef  scalar_t__ bwn_band_t ;
struct TYPE_3__ {scalar_t__ ipa5g_on; scalar_t__ ipa2g_on; } ;

/* Variables and functions */
 scalar_t__ BWN_BAND_2G ; 
 scalar_t__ BWN_BAND_5G ; 
 scalar_t__ bwn_current_band (struct bwn_mac*) ; 

__attribute__((used)) static inline bool bwn_nphy_ipa(struct bwn_mac *mac)
{
	bwn_band_t band = bwn_current_band(mac);
	return ((mac->mac_phy.phy_n->ipa2g_on && band == BWN_BAND_2G) ||
		(mac->mac_phy.phy_n->ipa5g_on && band == BWN_BAND_5G));
}