#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  union i40e_32byte_rx_desc {int dummy; } i40e_32byte_rx_desc ;
typedef  int /*<<< orphan*/  u32 ;
struct ixl_vsi {scalar_t__ enable_head_writeback; TYPE_4__* shared; int /*<<< orphan*/  media; int /*<<< orphan*/  ctx; scalar_t__ num_vlans; scalar_t__ id; struct i40e_hw* hw; void* dev; struct ixl_pf* back; } ;
struct TYPE_8__ {int /*<<< orphan*/  rss_table_size; int /*<<< orphan*/  num_rx_qp; int /*<<< orphan*/  num_tx_qp; } ;
struct TYPE_10__ {scalar_t__ type; int /*<<< orphan*/  port_addr; int /*<<< orphan*/  addr; int /*<<< orphan*/  perm_addr; } ;
struct TYPE_9__ {int api_maj_ver; int api_min_ver; int fw_maj_ver; int fw_min_ver; void* asq_buf_size; void* arq_buf_size; void* num_asq_entries; void* num_arq_entries; } ;
struct i40e_hw {TYPE_1__ func_caps; TYPE_3__ mac; TYPE_2__ aq; } ;
struct ixl_pf {struct i40e_hw hw; int /*<<< orphan*/  state; void* dev; struct ixl_vsi vsi; } ;
struct i40e_tx_desc {int dummy; } ;
struct i40e_filter_control_settings {int /*<<< orphan*/  hash_lut_size; int /*<<< orphan*/  enable_fdir; void* enable_macvlan; void* enable_ethtype; } ;
typedef  TYPE_4__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  filter ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  void* device_t ;
struct TYPE_12__ {int /*<<< orphan*/  ift_legacy_intr; } ;
struct TYPE_11__ {int isc_ntxqsets_max; int isc_nrxqsets_max; int* isc_ntxd; int* isc_nrxd; int /*<<< orphan*/  isc_capenable; int /*<<< orphan*/  isc_capabilities; int /*<<< orphan*/  isc_tx_csum_flags; int /*<<< orphan*/  isc_rss_table_size; int /*<<< orphan*/  isc_tx_tso_segsize_max; int /*<<< orphan*/  isc_tx_tso_size_max; int /*<<< orphan*/  isc_tx_tso_segments_max; int /*<<< orphan*/  isc_tx_nsegments; int /*<<< orphan*/  isc_msix_bar; void** isc_rxqsizes; TYPE_5__* isc_txrx; void** isc_txqsizes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSUM_OFFLOAD ; 
 int /*<<< orphan*/  DBA_ALIGN ; 
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  FALSE ; 
 int I40E_ERR_FIRMWARE_API_VERSION ; 
 int I40E_FW_API_VERSION_MAJOR ; 
 int I40E_FW_MINOR_VERSION (struct i40e_hw*) ; 
 int /*<<< orphan*/  I40E_HASH_LUT_SIZE_512 ; 
 int /*<<< orphan*/  I40E_HMC_MODEL_DIRECT_ONLY ; 
 scalar_t__ I40E_MAC_X722 ; 
 int /*<<< orphan*/  INIT_DBG_DEV (void*,char*) ; 
 void* IXL_AQ_BUF_SZ ; 
 void* IXL_AQ_LEN ; 
 int /*<<< orphan*/  IXL_CAPS ; 
 int /*<<< orphan*/  IXL_MAX_DMA_SEG_SIZE ; 
 int /*<<< orphan*/  IXL_MAX_TSO_SEGS ; 
 int /*<<< orphan*/  IXL_MAX_TX_SEGS ; 
 int /*<<< orphan*/  IXL_MSIX_BAR ; 
 int /*<<< orphan*/  IXL_PF_STATE_FW_LLDP_DISABLED ; 
 int /*<<< orphan*/  IXL_TSO_SIZE ; 
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct i40e_filter_control_settings*,int) ; 
 int /*<<< orphan*/  device_printf (void*,char*,...) ; 
 int /*<<< orphan*/  i40e_aq_set_dcb_parameters (struct i40e_hw*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_aq_stop_lldp (struct i40e_hw*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_clear_hw (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_clear_pxe_mode (struct i40e_hw*) ; 
 int i40e_configure_lan_hmc (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_get_mac_addr (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_get_port_mac_addr (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int i40e_init_adminq (struct i40e_hw*) ; 
 int i40e_init_lan_hmc (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i40e_init_shared_code (struct i40e_hw*) ; 
 int i40e_pf_reset (struct i40e_hw*) ; 
 scalar_t__ i40e_set_filter_control (struct i40e_hw*,struct i40e_filter_control_settings*) ; 
 int /*<<< orphan*/  i40e_shutdown_adminq (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_shutdown_lan_hmc (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_stat_str (struct i40e_hw*,int) ; 
 int i40e_validate_mac_addr (int /*<<< orphan*/ ) ; 
 void* iflib_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_media (int /*<<< orphan*/ ) ; 
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 
 TYPE_4__* iflib_get_softc_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_set_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ixl_allocate_pci_resources (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_free_pci_resources (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_get_fw_lldp_status (struct ixl_pf*) ; 
 int ixl_get_hw_capabilities (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_intr ; 
 int /*<<< orphan*/  ixl_print_nvm_version (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_save_pf_tunables (struct ixl_pf*) ; 
 TYPE_5__ ixl_txrx_dwb ; 
 TYPE_5__ ixl_txrx_hwb ; 
 void* roundup2 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixl_if_attach_pre(if_ctx_t ctx)
{
	device_t dev;
	struct ixl_pf *pf;
	struct i40e_hw *hw;
	struct ixl_vsi *vsi;
	if_softc_ctx_t scctx;
	struct i40e_filter_control_settings filter;
	enum i40e_status_code status;
	int error = 0;

	INIT_DBG_DEV(dev, "begin");

	dev = iflib_get_dev(ctx);
	pf = iflib_get_softc(ctx);

	vsi = &pf->vsi;
	vsi->back = pf;
	pf->dev = dev;
	hw = &pf->hw;

	vsi->dev = dev;
	vsi->hw = &pf->hw;
	vsi->id = 0;
	vsi->num_vlans = 0;
	vsi->ctx = ctx;
	vsi->media = iflib_get_media(ctx);
	vsi->shared = scctx = iflib_get_softc_ctx(ctx);

	/* Save tunable values */
	ixl_save_pf_tunables(pf);

	/* Do PCI setup - map BAR0, etc */
	if (ixl_allocate_pci_resources(pf)) {
		device_printf(dev, "Allocation of PCI resources failed\n");
		error = ENXIO;
		goto err_pci_res;
	}

	/* Establish a clean starting point */
	i40e_clear_hw(hw);
	status = i40e_pf_reset(hw);
	if (status) {
		device_printf(dev, "PF reset failure %s\n",
		    i40e_stat_str(hw, status));
		error = EIO;
		goto err_out;
	}

	/* Initialize the shared code */
	status = i40e_init_shared_code(hw);
	if (status) {
		device_printf(dev, "Unable to initialize shared code, error %s\n",
		    i40e_stat_str(hw, status));
		error = EIO;
		goto err_out;
	}

	/* Set up the admin queue */
	hw->aq.num_arq_entries = IXL_AQ_LEN;
	hw->aq.num_asq_entries = IXL_AQ_LEN;
	hw->aq.arq_buf_size = IXL_AQ_BUF_SZ;
	hw->aq.asq_buf_size = IXL_AQ_BUF_SZ;

	status = i40e_init_adminq(hw);
	if (status != 0 && status != I40E_ERR_FIRMWARE_API_VERSION) {
		device_printf(dev, "Unable to initialize Admin Queue, error %s\n",
		    i40e_stat_str(hw, status));
		error = EIO;
		goto err_out;
	}
	ixl_print_nvm_version(pf);

	if (status == I40E_ERR_FIRMWARE_API_VERSION) {
		device_printf(dev, "The driver for the device stopped "
		    "because the NVM image is newer than expected.\n");
		device_printf(dev, "You must install the most recent version of "
		    "the network driver.\n");
		error = EIO;
		goto err_out;
	}

        if (hw->aq.api_maj_ver == I40E_FW_API_VERSION_MAJOR &&
	    hw->aq.api_min_ver > I40E_FW_MINOR_VERSION(hw)) {
		device_printf(dev, "The driver for the device detected "
		    "a newer version of the NVM image than expected.\n");
		device_printf(dev, "Please install the most recent version "
		    "of the network driver.\n");
	} else if (hw->aq.api_maj_ver == 1 && hw->aq.api_min_ver < 4) {
		device_printf(dev, "The driver for the device detected "
		    "an older version of the NVM image than expected.\n");
		device_printf(dev, "Please update the NVM image.\n");
	}

	/* Clear PXE mode */
	i40e_clear_pxe_mode(hw);

	/* Get capabilities from the device */
	error = ixl_get_hw_capabilities(pf);
	if (error) {
		device_printf(dev, "get_hw_capabilities failed: %d\n",
		    error);
		goto err_get_cap;
	}

	/* Set up host memory cache */
	status = i40e_init_lan_hmc(hw, hw->func_caps.num_tx_qp,
	    hw->func_caps.num_rx_qp, 0, 0);
	if (status) {
		device_printf(dev, "init_lan_hmc failed: %s\n",
		    i40e_stat_str(hw, status));
		goto err_get_cap;
	}
	status = i40e_configure_lan_hmc(hw, I40E_HMC_MODEL_DIRECT_ONLY);
	if (status) {
		device_printf(dev, "configure_lan_hmc failed: %s\n",
		    i40e_stat_str(hw, status));
		goto err_mac_hmc;
	}

	/* Disable LLDP from the firmware for certain NVM versions */
	if (((pf->hw.aq.fw_maj_ver == 4) && (pf->hw.aq.fw_min_ver < 3)) ||
	    (pf->hw.aq.fw_maj_ver < 4)) {
		i40e_aq_stop_lldp(hw, TRUE, NULL);
		pf->state |= IXL_PF_STATE_FW_LLDP_DISABLED;
	}

	/* Get MAC addresses from hardware */
	i40e_get_mac_addr(hw, hw->mac.addr);
	error = i40e_validate_mac_addr(hw->mac.addr);
	if (error) {
		device_printf(dev, "validate_mac_addr failed: %d\n", error);
		goto err_mac_hmc;
	}
	bcopy(hw->mac.addr, hw->mac.perm_addr, ETHER_ADDR_LEN);
	iflib_set_mac(ctx, hw->mac.addr);
	i40e_get_port_mac_addr(hw, hw->mac.port_addr);

	/* Set up the device filtering */
	bzero(&filter, sizeof(filter));
	filter.enable_ethtype = TRUE;
	filter.enable_macvlan = TRUE;
	filter.enable_fdir = FALSE;
	filter.hash_lut_size = I40E_HASH_LUT_SIZE_512;
	if (i40e_set_filter_control(hw, &filter))
		device_printf(dev, "i40e_set_filter_control() failed\n");

	/* Query device FW LLDP status */
	ixl_get_fw_lldp_status(pf);
	/* Tell FW to apply DCB config on link up */
	i40e_aq_set_dcb_parameters(hw, true, NULL);

	/* Fill out iflib parameters */
	if (hw->mac.type == I40E_MAC_X722)
		scctx->isc_ntxqsets_max = scctx->isc_nrxqsets_max = 128;
	else
		scctx->isc_ntxqsets_max = scctx->isc_nrxqsets_max = 64;
	if (vsi->enable_head_writeback) {
		scctx->isc_txqsizes[0] = roundup2(scctx->isc_ntxd[0]
		    * sizeof(struct i40e_tx_desc) + sizeof(u32), DBA_ALIGN);
		scctx->isc_txrx = &ixl_txrx_hwb;
	} else {
		scctx->isc_txqsizes[0] = roundup2(scctx->isc_ntxd[0]
		    * sizeof(struct i40e_tx_desc), DBA_ALIGN);
		scctx->isc_txrx = &ixl_txrx_dwb;
	}
	scctx->isc_txrx->ift_legacy_intr = ixl_intr;
	scctx->isc_rxqsizes[0] = roundup2(scctx->isc_nrxd[0]
	    * sizeof(union i40e_32byte_rx_desc), DBA_ALIGN);
	scctx->isc_msix_bar = PCIR_BAR(IXL_MSIX_BAR);
	scctx->isc_tx_nsegments = IXL_MAX_TX_SEGS;
	scctx->isc_tx_tso_segments_max = IXL_MAX_TSO_SEGS;
	scctx->isc_tx_tso_size_max = IXL_TSO_SIZE;
	scctx->isc_tx_tso_segsize_max = IXL_MAX_DMA_SEG_SIZE;
	scctx->isc_rss_table_size = pf->hw.func_caps.rss_table_size;
	scctx->isc_tx_csum_flags = CSUM_OFFLOAD;
	scctx->isc_capabilities = scctx->isc_capenable = IXL_CAPS;

	INIT_DBG_DEV(dev, "end");
	return (0);

err_mac_hmc:
	i40e_shutdown_lan_hmc(hw);
err_get_cap:
	i40e_shutdown_adminq(hw);
err_out:
	ixl_free_pci_resources(pf);
err_pci_res:
	return (error);
}