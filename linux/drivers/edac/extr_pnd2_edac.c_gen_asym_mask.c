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
struct b_cr_slice_channel_hash {scalar_t__ enable_pmi_dual_data_mode; scalar_t__ ch_1_disabled; scalar_t__ slice_1_disabled; scalar_t__ slice_0_mem_disabled; } ;
struct b_cr_asym_mem_region1_mchbar {int slice1_asym_channel_select; scalar_t__ slice1_asym_enable; } ;
struct b_cr_asym_mem_region0_mchbar {int slice0_asym_channel_select; scalar_t__ slice0_asym_enable; } ;
struct b_cr_asym_2way_mem_region_mchbar {size_t asym_2way_intlv_mode; scalar_t__ asym_2way_interleave_enable; } ;

/* Variables and functions */

__attribute__((used)) static int gen_asym_mask(struct b_cr_slice_channel_hash *p,
			 struct b_cr_asym_mem_region0_mchbar *as0,
			 struct b_cr_asym_mem_region1_mchbar *as1,
			 struct b_cr_asym_2way_mem_region_mchbar *as2way)
{
	const int intlv[] = { 0x5, 0xA, 0x3, 0xC };
	int mask = 0;

	if (as2way->asym_2way_interleave_enable)
		mask = intlv[as2way->asym_2way_intlv_mode];
	if (as0->slice0_asym_enable)
		mask |= (1 << as0->slice0_asym_channel_select);
	if (as1->slice1_asym_enable)
		mask |= (4 << as1->slice1_asym_channel_select);
	if (p->slice_0_mem_disabled)
		mask &= 0xc;
	if (p->slice_1_disabled)
		mask &= 0x3;
	if (p->ch_1_disabled || p->enable_pmi_dual_data_mode)
		mask &= 0x5;

	return mask;
}