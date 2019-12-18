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
typedef  size_t uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct sq_cfg_msg {size_t sq_num; } ;
struct nicpf {int /*<<< orphan*/ * vf_lmac_map; } ;

/* Variables and functions */
 int MAX_BGX_CHANS_PER_LMAC ; 
 int NIC_CHANS_PER_INF ; 
 int NIC_GET_BGX_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
 int NIC_GET_LMAC_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
 int NIC_HW_MAX_FRS ; 
 int NIC_MAX_TL3 ; 
 int NIC_MAX_TL4 ; 
 int NIC_PF_CHAN_0_255_TX_CFG ; 
 int NIC_PF_QSET_0_127_SQ_0_7_CFG2 ; 
 int NIC_PF_TL2_0_63_CFG ; 
 int NIC_PF_TL2_0_63_PRI ; 
 int NIC_PF_TL3A_0_63_CFG ; 
 int NIC_PF_TL3_0_255_CFG ; 
 int NIC_PF_TL3_0_255_CHAN ; 
 int NIC_PF_TL4_0_1023_CFG ; 
 int NIC_QS_ID_SHIFT ; 
 int NIC_Q_NUM_SHIFT ; 
 int NIC_TL4_PER_BGX ; 
 int NIC_TL4_PER_LMAC ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,int,int) ; 

__attribute__((used)) static void
nic_tx_channel_cfg(struct nicpf *nic, uint8_t vnic, struct sq_cfg_msg *sq)
{
	uint32_t bgx, lmac, chan;
	uint32_t tl2, tl3, tl4;
	uint32_t rr_quantum;
	uint8_t sq_idx = sq->sq_num;
	uint8_t pqs_vnic;

	pqs_vnic = vnic;

	bgx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[pqs_vnic]);
	lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[pqs_vnic]);

	/* 24 bytes for FCS, IPG and preamble */
	rr_quantum = ((NIC_HW_MAX_FRS + 24) / 4);

	tl4 = (lmac * NIC_TL4_PER_LMAC) + (bgx * NIC_TL4_PER_BGX);
	tl4 += sq_idx;

	tl3 = tl4 / (NIC_MAX_TL4 / NIC_MAX_TL3);
	nic_reg_write(nic, NIC_PF_QSET_0_127_SQ_0_7_CFG2 |
	    ((uint64_t)vnic << NIC_QS_ID_SHIFT) |
	    ((uint32_t)sq_idx << NIC_Q_NUM_SHIFT), tl4);
	nic_reg_write(nic, NIC_PF_TL4_0_1023_CFG | (tl4 << 3),
	    ((uint64_t)vnic << 27) | ((uint32_t)sq_idx << 24) | rr_quantum);

	nic_reg_write(nic, NIC_PF_TL3_0_255_CFG | (tl3 << 3), rr_quantum);
	chan = (lmac * MAX_BGX_CHANS_PER_LMAC) + (bgx * NIC_CHANS_PER_INF);
	nic_reg_write(nic, NIC_PF_TL3_0_255_CHAN | (tl3 << 3), chan);
	/* Enable backpressure on the channel */
	nic_reg_write(nic, NIC_PF_CHAN_0_255_TX_CFG | (chan << 3), 1);

	tl2 = tl3 >> 2;
	nic_reg_write(nic, NIC_PF_TL3A_0_63_CFG | (tl2 << 3), tl2);
	nic_reg_write(nic, NIC_PF_TL2_0_63_CFG | (tl2 << 3), rr_quantum);
	/* No priorities as of now */
	nic_reg_write(nic, NIC_PF_TL2_0_63_PRI | (tl2 << 3), 0x00);
}