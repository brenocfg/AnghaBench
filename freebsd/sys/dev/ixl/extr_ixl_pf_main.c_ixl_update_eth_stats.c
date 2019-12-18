#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct i40e_eth_stats {int /*<<< orphan*/  tx_broadcast; int /*<<< orphan*/  tx_multicast; int /*<<< orphan*/  tx_unicast; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_broadcast; int /*<<< orphan*/  rx_multicast; int /*<<< orphan*/  rx_unicast; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_discards; int /*<<< orphan*/  tx_errors; } ;
struct TYPE_2__ {int /*<<< orphan*/  stat_counter_idx; } ;
struct ixl_vsi {int stat_offsets_loaded; struct i40e_eth_stats eth_stats_offsets; struct i40e_eth_stats eth_stats; TYPE_1__ info; scalar_t__ back; } ;
struct i40e_hw_port_stats {int dummy; } ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {struct i40e_hw_port_stats stats; struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_GLV_BPRCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_GLV_BPRCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_GLV_BPTCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_GLV_BPTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_GLV_GORCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_GLV_GORCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_GLV_GOTCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_GLV_GOTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_GLV_MPRCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_GLV_MPRCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_GLV_MPTCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_GLV_MPTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_GLV_RDPC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_GLV_TEPC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_GLV_UPRCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_GLV_UPRCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_GLV_UPTCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_GLV_UPTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_stat_update32 (struct i40e_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixl_stat_update48 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ixl_update_eth_stats(struct ixl_vsi *vsi)
{
	struct ixl_pf *pf = (struct ixl_pf *)vsi->back;
	struct i40e_hw *hw = &pf->hw;
	struct i40e_eth_stats *es;
	struct i40e_eth_stats *oes;
	struct i40e_hw_port_stats *nsd;
	u16 stat_idx = vsi->info.stat_counter_idx;

	es = &vsi->eth_stats;
	oes = &vsi->eth_stats_offsets;
	nsd = &pf->stats;

	/* Gather up the stats that the hw collects */
	ixl_stat_update32(hw, I40E_GLV_TEPC(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->tx_errors, &es->tx_errors);
	ixl_stat_update32(hw, I40E_GLV_RDPC(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->rx_discards, &es->rx_discards);

	ixl_stat_update48(hw, I40E_GLV_GORCH(stat_idx),
			   I40E_GLV_GORCL(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->rx_bytes, &es->rx_bytes);
	ixl_stat_update48(hw, I40E_GLV_UPRCH(stat_idx),
			   I40E_GLV_UPRCL(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->rx_unicast, &es->rx_unicast);
	ixl_stat_update48(hw, I40E_GLV_MPRCH(stat_idx),
			   I40E_GLV_MPRCL(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->rx_multicast, &es->rx_multicast);
	ixl_stat_update48(hw, I40E_GLV_BPRCH(stat_idx),
			   I40E_GLV_BPRCL(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->rx_broadcast, &es->rx_broadcast);

	ixl_stat_update48(hw, I40E_GLV_GOTCH(stat_idx),
			   I40E_GLV_GOTCL(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->tx_bytes, &es->tx_bytes);
	ixl_stat_update48(hw, I40E_GLV_UPTCH(stat_idx),
			   I40E_GLV_UPTCL(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->tx_unicast, &es->tx_unicast);
	ixl_stat_update48(hw, I40E_GLV_MPTCH(stat_idx),
			   I40E_GLV_MPTCL(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->tx_multicast, &es->tx_multicast);
	ixl_stat_update48(hw, I40E_GLV_BPTCH(stat_idx),
			   I40E_GLV_BPTCL(stat_idx),
			   vsi->stat_offsets_loaded,
			   &oes->tx_broadcast, &es->tx_broadcast);
	vsi->stat_offsets_loaded = true;
}