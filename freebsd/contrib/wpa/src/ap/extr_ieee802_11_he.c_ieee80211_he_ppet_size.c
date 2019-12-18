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

/* Variables and functions */
 int const HE_PHYCAP_PPE_THRESHOLD_PRESENT ; 
 size_t HE_PHYCAP_PPE_THRESHOLD_PRESENT_IDX ; 
 int HE_PPE_THRES_NSS_MASK ; 
 int HE_PPE_THRES_RU_INDEX_BITMASK_MASK ; 
 int HE_PPE_THRES_RU_INDEX_BITMASK_SHIFT ; 

__attribute__((used)) static u8 ieee80211_he_ppet_size(u8 ppe_thres_hdr, const u8 *phy_cap_info)
{
	u8 sz = 0, ru;

	if ((phy_cap_info[HE_PHYCAP_PPE_THRESHOLD_PRESENT_IDX] &
	     HE_PHYCAP_PPE_THRESHOLD_PRESENT) == 0)
		return 0;

	ru = (ppe_thres_hdr >> HE_PPE_THRES_RU_INDEX_BITMASK_SHIFT) &
		HE_PPE_THRES_RU_INDEX_BITMASK_MASK;
	while (ru) {
		if (ru & 0x1)
			sz++;
		ru >>= 1;
	}

	sz *= 1 + (ppe_thres_hdr & HE_PPE_THRES_NSS_MASK);
	sz = (sz * 6) + 7;
	if (sz % 8)
		sz += 8;
	sz /= 8;

	return sz;
}