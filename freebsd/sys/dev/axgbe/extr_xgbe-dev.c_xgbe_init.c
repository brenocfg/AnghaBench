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
struct xgbe_desc_if {int /*<<< orphan*/  (* wrapper_rx_desc_init ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* wrapper_tx_desc_init ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {int /*<<< orphan*/  rx_threshold; int /*<<< orphan*/  tx_threshold; int /*<<< orphan*/  rx_sf_mode; int /*<<< orphan*/  tx_sf_mode; struct xgbe_desc_if desc_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub2 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_checksum_offload (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_dma_bus (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_dma_cache (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_flow_control (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_flow_control_threshold (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_jumbo_enable (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_mac_address (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_mac_speed (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_mmc (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_mtl_mode (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_osp_mode (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_pblx8 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_queue_mapping (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_rsf_mode (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_config_rss (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_rx_buffer_size (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_rx_coalesce (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_rx_fifo_size (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_rx_mode (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_rx_pbl_val (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_rx_threshold (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_config_sph_mode (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_tsf_mode (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_config_tso_mode (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_tx_coalesce (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_tx_fifo_size (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_tx_pbl_val (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_tx_threshold (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_config_vlan_support (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_enable_dma_interrupts (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_enable_mac_interrupts (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_enable_mtl_interrupts (struct xgbe_prv_data*) ; 
 int xgbe_flush_tx_queues (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_init(struct xgbe_prv_data *pdata)
{
	struct xgbe_desc_if *desc_if = &pdata->desc_if;
	int ret;

	DBGPR("-->xgbe_init\n");

	/* Flush Tx queues */
	ret = xgbe_flush_tx_queues(pdata);
	if (ret)
		return ret;

	/*
	 * Initialize DMA related features
	 */
	xgbe_config_dma_bus(pdata);
	xgbe_config_dma_cache(pdata);
	xgbe_config_osp_mode(pdata);
	xgbe_config_pblx8(pdata);
	xgbe_config_tx_pbl_val(pdata);
	xgbe_config_rx_pbl_val(pdata);
	xgbe_config_rx_coalesce(pdata);
	xgbe_config_tx_coalesce(pdata);
	xgbe_config_rx_buffer_size(pdata);
	xgbe_config_tso_mode(pdata);
	xgbe_config_sph_mode(pdata);
	xgbe_config_rss(pdata);
	desc_if->wrapper_tx_desc_init(pdata);
	desc_if->wrapper_rx_desc_init(pdata);
	xgbe_enable_dma_interrupts(pdata);

	/*
	 * Initialize MTL related features
	 */
	xgbe_config_mtl_mode(pdata);
	xgbe_config_queue_mapping(pdata);
	xgbe_config_tsf_mode(pdata, pdata->tx_sf_mode);
	xgbe_config_rsf_mode(pdata, pdata->rx_sf_mode);
	xgbe_config_tx_threshold(pdata, pdata->tx_threshold);
	xgbe_config_rx_threshold(pdata, pdata->rx_threshold);
	xgbe_config_tx_fifo_size(pdata);
	xgbe_config_rx_fifo_size(pdata);
	xgbe_config_flow_control_threshold(pdata);
	/*TODO: Error Packet and undersized good Packet forwarding enable
		(FEP and FUP)
	 */
	xgbe_enable_mtl_interrupts(pdata);

	/*
	 * Initialize MAC related features
	 */
	xgbe_config_mac_address(pdata);
	xgbe_config_rx_mode(pdata);
	xgbe_config_jumbo_enable(pdata);
	xgbe_config_flow_control(pdata);
	xgbe_config_mac_speed(pdata);
	xgbe_config_checksum_offload(pdata);
	xgbe_config_vlan_support(pdata);
	xgbe_config_mmc(pdata);
	xgbe_enable_mac_interrupts(pdata);

	DBGPR("<--xgbe_init\n");

	return 0;
}