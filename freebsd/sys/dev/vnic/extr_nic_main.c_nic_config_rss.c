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
struct rss_cfg_msg {size_t vf_id; int tbl_offset; int tbl_len; int* ind_tbl; int hash_bits; } ;
struct nicpf {int* rssi_base; int* cpi_base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int NIC_PF_CPI_0_2047_CFG ; 
 int NIC_PF_MPI_0_2047_CFG ; 
 int NIC_PF_RSSI_0_4097_RQ ; 
 int nic_reg_read (struct nicpf*,int) ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,int,int) ; 
 scalar_t__ pass1_silicon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nic_config_rss(struct nicpf *nic, struct rss_cfg_msg *cfg)
{
	uint8_t qset, idx;
	uint64_t cpi_cfg, cpi_base, rssi_base, rssi;
	uint64_t idx_addr;

	idx = 0;
	rssi_base = nic->rssi_base[cfg->vf_id] + cfg->tbl_offset;

	rssi = rssi_base;
	qset = cfg->vf_id;

	for (; rssi < (rssi_base + cfg->tbl_len); rssi++) {
		nic_reg_write(nic, NIC_PF_RSSI_0_4097_RQ | (rssi << 3),
		    (qset << 3) | (cfg->ind_tbl[idx] & 0x7));
		idx++;
	}

	cpi_base = nic->cpi_base[cfg->vf_id];
	if (pass1_silicon(nic->dev))
		idx_addr = NIC_PF_CPI_0_2047_CFG;
	else
		idx_addr = NIC_PF_MPI_0_2047_CFG;
	cpi_cfg = nic_reg_read(nic, idx_addr | (cpi_base << 3));
	cpi_cfg &= ~(0xFUL << 20);
	cpi_cfg |= (cfg->hash_bits << 20);
	nic_reg_write(nic, idx_addr | (cpi_base << 3), cpi_cfg);
}