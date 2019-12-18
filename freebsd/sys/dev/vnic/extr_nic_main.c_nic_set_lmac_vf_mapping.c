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
typedef  int uint64_t ;
struct nicpf {int flags; scalar_t__ num_vf_en; int /*<<< orphan*/ * vf_lmac_map; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_NUM_VF_ENABLED ; 
 int MAX_LMAC_PER_BGX ; 
 int NIC_HW_MAX_FRS ; 
 int NIC_MAX_BGX ; 
 scalar_t__ NIC_PF_LMAC_0_7_CREDIT ; 
 int /*<<< orphan*/  NIC_SET_VF_LMAC_MAP (int,int) ; 
 int NIC_TNS_ENABLED ; 
 int bgx_get_lmac_count (int /*<<< orphan*/ ,int) ; 
 unsigned int bgx_get_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,scalar_t__,int) ; 

__attribute__((used)) static void
nic_set_lmac_vf_mapping(struct nicpf *nic)
{
	unsigned bgx_map = bgx_get_map(nic->node);
	int bgx, next_bgx_lmac = 0;
	int lmac, lmac_cnt = 0;
	uint64_t lmac_credit;

	nic->num_vf_en = 0;
	if (nic->flags & NIC_TNS_ENABLED) {
		nic->num_vf_en = DEFAULT_NUM_VF_ENABLED;
		return;
	}

	for (bgx = 0; bgx < NIC_MAX_BGX; bgx++) {
		if ((bgx_map & (1 << bgx)) == 0)
			continue;
		lmac_cnt = bgx_get_lmac_count(nic->node, bgx);
		for (lmac = 0; lmac < lmac_cnt; lmac++)
			nic->vf_lmac_map[next_bgx_lmac++] =
						NIC_SET_VF_LMAC_MAP(bgx, lmac);
		nic->num_vf_en += lmac_cnt;

		/* Program LMAC credits */
		lmac_credit = (1UL << 1); /* channel credit enable */
		lmac_credit |= (0x1ff << 2); /* Max outstanding pkt count */
		/* 48KB BGX Tx buffer size, each unit is of size 16bytes */
		lmac_credit |= (((((48 * 1024) / lmac_cnt) -
		    NIC_HW_MAX_FRS) / 16) << 12);
		lmac = bgx * MAX_LMAC_PER_BGX;
		for (; lmac < lmac_cnt + (bgx * MAX_LMAC_PER_BGX); lmac++) {
			nic_reg_write(nic, NIC_PF_LMAC_0_7_CREDIT + (lmac * 8),
			    lmac_credit);
		}
	}
}