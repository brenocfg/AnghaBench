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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  size_t uint32_t ;
struct nicpf {size_t rss_ind_tbl_size; int* cpi_base; int* rssi_base; int /*<<< orphan*/  dev; int /*<<< orphan*/ * vf_lmac_map; } ;
struct cpi_cfg_msg {size_t vf_id; scalar_t__ cpi_alg; int rq_cnt; } ;

/* Variables and functions */
 scalar_t__ CPI_ALG_DIFF ; 
 scalar_t__ CPI_ALG_NONE ; 
 scalar_t__ CPI_ALG_VLAN ; 
 scalar_t__ CPI_ALG_VLAN16 ; 
 size_t MAX_BGX_CHANS_PER_LMAC ; 
 size_t NIC_CHANS_PER_INF ; 
 size_t NIC_CPI_PER_BGX ; 
 size_t NIC_GET_BGX_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
 size_t NIC_GET_LMAC_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
 size_t NIC_MAX_CPI_PER_LMAC ; 
 size_t NIC_PF_CHAN_0_255_RX_BP_CFG ; 
 size_t NIC_PF_CHAN_0_255_RX_CFG ; 
 int NIC_PF_CPI_0_2047_CFG ; 
 int NIC_PF_MPI_0_2047_CFG ; 
 int NIC_PF_RSSI_0_4097_RQ ; 
 size_t NIC_RSSI_PER_BGX ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,int,size_t) ; 
 scalar_t__ pass1_silicon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nic_config_cpi(struct nicpf *nic, struct cpi_cfg_msg *cfg)
{
	uint32_t vnic, bgx, lmac, chan;
	uint32_t padd, cpi_count = 0;
	uint64_t cpi_base, cpi, rssi_base, rssi;
	uint8_t qset, rq_idx = 0;

	vnic = cfg->vf_id;
	bgx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vnic]);
	lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vnic]);

	chan = (lmac * MAX_BGX_CHANS_PER_LMAC) + (bgx * NIC_CHANS_PER_INF);
	cpi_base = (lmac * NIC_MAX_CPI_PER_LMAC) + (bgx * NIC_CPI_PER_BGX);
	rssi_base = (lmac * nic->rss_ind_tbl_size) + (bgx * NIC_RSSI_PER_BGX);

	/* Rx channel configuration */
	nic_reg_write(nic, NIC_PF_CHAN_0_255_RX_BP_CFG | (chan << 3),
	    (1UL << 63) | (vnic << 0));
	nic_reg_write(nic, NIC_PF_CHAN_0_255_RX_CFG | (chan << 3),
	    ((uint64_t)cfg->cpi_alg << 62) | (cpi_base << 48));

	if (cfg->cpi_alg == CPI_ALG_NONE)
		cpi_count = 1;
	else if (cfg->cpi_alg == CPI_ALG_VLAN) /* 3 bits of PCP */
		cpi_count = 8;
	else if (cfg->cpi_alg == CPI_ALG_VLAN16) /* 3 bits PCP + DEI */
		cpi_count = 16;
	else if (cfg->cpi_alg == CPI_ALG_DIFF) /* 6bits DSCP */
		cpi_count = NIC_MAX_CPI_PER_LMAC;

	/* RSS Qset, Qidx mapping */
	qset = cfg->vf_id;
	rssi = rssi_base;
	for (; rssi < (rssi_base + cfg->rq_cnt); rssi++) {
		nic_reg_write(nic, NIC_PF_RSSI_0_4097_RQ | (rssi << 3),
		    (qset << 3) | rq_idx);
		rq_idx++;
	}

	rssi = 0;
	cpi = cpi_base;
	for (; cpi < (cpi_base + cpi_count); cpi++) {
		/* Determine port to channel adder */
		if (cfg->cpi_alg != CPI_ALG_DIFF)
			padd = cpi % cpi_count;
		else
			padd = cpi % 8; /* 3 bits CS out of 6bits DSCP */

		/* Leave RSS_SIZE as '0' to disable RSS */
		if (pass1_silicon(nic->dev)) {
			nic_reg_write(nic, NIC_PF_CPI_0_2047_CFG | (cpi << 3),
			    (vnic << 24) | (padd << 16) | (rssi_base + rssi));
		} else {
			/* Set MPI_ALG to '0' to disable MCAM parsing */
			nic_reg_write(nic, NIC_PF_CPI_0_2047_CFG | (cpi << 3),
			    (padd << 16));
			/* MPI index is same as CPI if MPI_ALG is not enabled */
			nic_reg_write(nic, NIC_PF_MPI_0_2047_CFG | (cpi << 3),
			    (vnic << 24) | (rssi_base + rssi));
		}

		if ((rssi + 1) >= cfg->rq_cnt)
			continue;

		if (cfg->cpi_alg == CPI_ALG_VLAN)
			rssi++;
		else if (cfg->cpi_alg == CPI_ALG_VLAN16)
			rssi = ((cpi - cpi_base) & 0xe) >> 1;
		else if (cfg->cpi_alg == CPI_ALG_DIFF)
			rssi = ((cpi - cpi_base) & 0x38) >> 3;
	}
	nic->cpi_base[cfg->vf_id] = cpi_base;
	nic->rssi_base[cfg->vf_id] = rssi_base;
}