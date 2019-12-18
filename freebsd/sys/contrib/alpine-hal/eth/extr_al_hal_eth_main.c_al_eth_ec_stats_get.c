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
struct al_hal_eth_adapter {TYPE_2__* ec_regs_base; } ;
struct al_eth_ec_stats {void* eee_in; void* rfw_in_prot_i_drop; void* rfw_in_ctrl_drop; void* rfw_in_mac_ndet_drop; void* rfw_in_mac_drop; void* rfw_in_vlan_nexist; void* rfw_in_vlan_exist; void* rfw_in_bc; void* rfw_in_mc; void* rfw_in_parse_drop; void* rfw_in_vlan_drop; void* rfw_in_rx_pkt; void* tfw_out_tx_pkt; void* tfw_in_tx_pkt; void* tpm_tx_pkt; void* tpe_out_tx_pkt; void* tpe_in_tx_pkt; void* rpe_3_out_rx_pkt; void* rpe_3_in_rx_pkt; void* rpe_2_out_rx_pkt; void* rpe_2_in_rx_pkt; void* rpe_1_out_rx_pkt; void* rpe_1_in_rx_pkt; void* rxf_out_drop_2_pkt; void* rxf_out_drop_1_pkt; void* rxf_out_rx_2_pkt; void* rxf_out_rx_1_pkt; void* lbf_in_fifo_err; void* lbf_in_rx_pkt; void* rxf_in_fifo_err; void* rxf_in_rx_pkt; void* faf_out_drop; void* faf_out_rx_long; void* faf_out_rx_short; void* faf_out_rx_pkt; void* faf_in_rx_long; void* faf_in_rx_short; void* faf_in_rx_pkt; } ;
struct TYPE_3__ {int /*<<< orphan*/  eee_in; int /*<<< orphan*/  rfw_in_prot_i_drop; int /*<<< orphan*/  rfw_in_ctrl_drop; int /*<<< orphan*/  rfw_in_mac_ndet_drop; int /*<<< orphan*/  rfw_in_mac_drop; int /*<<< orphan*/  rfw_in_vlan_nexist; int /*<<< orphan*/  rfw_in_vlan_exist; int /*<<< orphan*/  rfw_in_bc; int /*<<< orphan*/  rfw_in_mc; int /*<<< orphan*/  rfw_in_parse_drop; int /*<<< orphan*/  rfw_in_vlan_drop; int /*<<< orphan*/  rfw_in_rx_pkt; int /*<<< orphan*/  tfw_out_tx_pkt; int /*<<< orphan*/  tfw_in_tx_pkt; int /*<<< orphan*/  tpm_tx_pkt; int /*<<< orphan*/  tpe_out_tx_pkt; int /*<<< orphan*/  tpe_in_tx_pkt; int /*<<< orphan*/  rpe_3_out_rx_pkt; int /*<<< orphan*/  rpe_3_in_rx_pkt; int /*<<< orphan*/  rpe_2_out_rx_pkt; int /*<<< orphan*/  rpe_2_in_rx_pkt; int /*<<< orphan*/  rpe_1_out_rx_pkt; int /*<<< orphan*/  rpe_1_in_rx_pkt; int /*<<< orphan*/  rxf_out_drop_2_pkt; int /*<<< orphan*/  rxf_out_drop_1_pkt; int /*<<< orphan*/  rxf_out_rx_2_pkt; int /*<<< orphan*/  rxf_out_rx_1_pkt; int /*<<< orphan*/  lbf_in_fifo_err; int /*<<< orphan*/  lbf_in_rx_pkt; int /*<<< orphan*/  rxf_in_fifo_err; int /*<<< orphan*/  rxf_in_rx_pkt; int /*<<< orphan*/  faf_out_drop; int /*<<< orphan*/  faf_out_rx_long; int /*<<< orphan*/  faf_out_rx_short; int /*<<< orphan*/  faf_out_rx_pkt; int /*<<< orphan*/  faf_in_rx_long; int /*<<< orphan*/  faf_in_rx_short; int /*<<< orphan*/  faf_in_rx_pkt; } ;
struct TYPE_4__ {TYPE_1__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_assert (struct al_eth_ec_stats*) ; 
 void* al_reg_read32 (int /*<<< orphan*/ *) ; 

int al_eth_ec_stats_get(struct al_hal_eth_adapter *adapter, struct al_eth_ec_stats *stats)
{
	al_assert(stats);
	stats->faf_in_rx_pkt = al_reg_read32(&adapter->ec_regs_base->stat.faf_in_rx_pkt);
	stats->faf_in_rx_short = al_reg_read32(&adapter->ec_regs_base->stat.faf_in_rx_short);
	stats->faf_in_rx_long = al_reg_read32(&adapter->ec_regs_base->stat.faf_in_rx_long);
	stats->faf_out_rx_pkt = al_reg_read32(&adapter->ec_regs_base->stat.faf_out_rx_pkt);
	stats->faf_out_rx_short = al_reg_read32(&adapter->ec_regs_base->stat.faf_out_rx_short);
	stats->faf_out_rx_long = al_reg_read32(&adapter->ec_regs_base->stat.faf_out_rx_long);
	stats->faf_out_drop = al_reg_read32(&adapter->ec_regs_base->stat.faf_out_drop);
	stats->rxf_in_rx_pkt = al_reg_read32(&adapter->ec_regs_base->stat.rxf_in_rx_pkt);
	stats->rxf_in_fifo_err = al_reg_read32(&adapter->ec_regs_base->stat.rxf_in_fifo_err);
	stats->lbf_in_rx_pkt = al_reg_read32(&adapter->ec_regs_base->stat.lbf_in_rx_pkt);
	stats->lbf_in_fifo_err = al_reg_read32(&adapter->ec_regs_base->stat.lbf_in_fifo_err);
	stats->rxf_out_rx_1_pkt = al_reg_read32(&adapter->ec_regs_base->stat.rxf_out_rx_1_pkt);
	stats->rxf_out_rx_2_pkt = al_reg_read32(&adapter->ec_regs_base->stat.rxf_out_rx_2_pkt);
	stats->rxf_out_drop_1_pkt = al_reg_read32(&adapter->ec_regs_base->stat.rxf_out_drop_1_pkt);
	stats->rxf_out_drop_2_pkt = al_reg_read32(&adapter->ec_regs_base->stat.rxf_out_drop_2_pkt);
	stats->rpe_1_in_rx_pkt = al_reg_read32(&adapter->ec_regs_base->stat.rpe_1_in_rx_pkt);
	stats->rpe_1_out_rx_pkt = al_reg_read32(&adapter->ec_regs_base->stat.rpe_1_out_rx_pkt);
	stats->rpe_2_in_rx_pkt = al_reg_read32(&adapter->ec_regs_base->stat.rpe_2_in_rx_pkt);
	stats->rpe_2_out_rx_pkt = al_reg_read32(&adapter->ec_regs_base->stat.rpe_2_out_rx_pkt);
	stats->rpe_3_in_rx_pkt = al_reg_read32(&adapter->ec_regs_base->stat.rpe_3_in_rx_pkt);
	stats->rpe_3_out_rx_pkt = al_reg_read32(&adapter->ec_regs_base->stat.rpe_3_out_rx_pkt);
	stats->tpe_in_tx_pkt = al_reg_read32(&adapter->ec_regs_base->stat.tpe_in_tx_pkt);
	stats->tpe_out_tx_pkt = al_reg_read32(&adapter->ec_regs_base->stat.tpe_out_tx_pkt);
	stats->tpm_tx_pkt = al_reg_read32(&adapter->ec_regs_base->stat.tpm_tx_pkt);
	stats->tfw_in_tx_pkt = al_reg_read32(&adapter->ec_regs_base->stat.tfw_in_tx_pkt);
	stats->tfw_out_tx_pkt = al_reg_read32(&adapter->ec_regs_base->stat.tfw_out_tx_pkt);
	stats->rfw_in_rx_pkt = al_reg_read32(&adapter->ec_regs_base->stat.rfw_in_rx_pkt);
	stats->rfw_in_vlan_drop = al_reg_read32(&adapter->ec_regs_base->stat.rfw_in_vlan_drop);
	stats->rfw_in_parse_drop = al_reg_read32(&adapter->ec_regs_base->stat.rfw_in_parse_drop);
	stats->rfw_in_mc = al_reg_read32(&adapter->ec_regs_base->stat.rfw_in_mc);
	stats->rfw_in_bc = al_reg_read32(&adapter->ec_regs_base->stat.rfw_in_bc);
	stats->rfw_in_vlan_exist = al_reg_read32(&adapter->ec_regs_base->stat.rfw_in_vlan_exist);
	stats->rfw_in_vlan_nexist = al_reg_read32(&adapter->ec_regs_base->stat.rfw_in_vlan_nexist);
	stats->rfw_in_mac_drop = al_reg_read32(&adapter->ec_regs_base->stat.rfw_in_mac_drop);
	stats->rfw_in_mac_ndet_drop = al_reg_read32(&adapter->ec_regs_base->stat.rfw_in_mac_ndet_drop);
	stats->rfw_in_ctrl_drop = al_reg_read32(&adapter->ec_regs_base->stat.rfw_in_ctrl_drop);
	stats->rfw_in_prot_i_drop = al_reg_read32(&adapter->ec_regs_base->stat.rfw_in_prot_i_drop);
	stats->eee_in = al_reg_read32(&adapter->ec_regs_base->stat.eee_in);
	return 0;
}