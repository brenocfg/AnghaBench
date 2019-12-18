#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  union ixgbe_adv_tx_desc {int dummy; } ixgbe_adv_tx_desc ;
typedef  union ixgbe_adv_rx_desc {int dummy; } ixgbe_adv_rx_desc ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_13__ {int type; int /*<<< orphan*/  addr; } ;
struct TYPE_12__ {void* reset_if_overtemp; int /*<<< orphan*/  smart_speed; } ;
struct TYPE_11__ {int /*<<< orphan*/  requested_mode; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* init_params ) (struct ixgbe_hw*) ;} ;
struct TYPE_10__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_5__ mac; TYPE_4__ phy; TYPE_3__ fc; int /*<<< orphan*/  allow_unsupported_sfp; TYPE_2__ mbx; int /*<<< orphan*/  subsystem_device_id; int /*<<< orphan*/  subsystem_vendor_id; int /*<<< orphan*/  revision_id; int /*<<< orphan*/  device_id; int /*<<< orphan*/  vendor_id; struct adapter* back; } ;
struct adapter {int feat_en; struct ixgbe_hw hw; void* sfp_probe; int /*<<< orphan*/  media; TYPE_6__* shared; int /*<<< orphan*/  dev; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_6__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_15__ {int /*<<< orphan*/  ift_legacy_intr; } ;
struct TYPE_14__ {int isc_rss_table_size; int isc_ntxqsets_max; int isc_nrxqsets_max; int* isc_ntxd; int* isc_nrxd; int isc_tx_csum_flags; int /*<<< orphan*/  isc_capenable; int /*<<< orphan*/  isc_capabilities; TYPE_7__* isc_txrx; int /*<<< orphan*/  isc_tx_tso_segsize_max; int /*<<< orphan*/  isc_tx_tso_size_max; int /*<<< orphan*/  isc_tx_nsegments; int /*<<< orphan*/  isc_tx_tso_segments_max; int /*<<< orphan*/  isc_msix_bar; void** isc_rxqsizes; void** isc_txqsizes; } ;

/* Variables and functions */
 int CSUM_IP ; 
 int CSUM_IP6_SCTP ; 
 int CSUM_IP6_TCP ; 
 int CSUM_IP6_TSO ; 
 int CSUM_IP6_UDP ; 
 int CSUM_SCTP ; 
 int CSUM_TCP ; 
 int CSUM_TSO ; 
 int CSUM_UDP ; 
 int /*<<< orphan*/  DBA_ALIGN ; 
 int EIO ; 
 int ENXIO ; 
 void* FALSE ; 
 int /*<<< orphan*/  INIT_DEBUGOUT (char*) ; 
 int /*<<< orphan*/  IXGBE_82598_SCATTER ; 
 int /*<<< orphan*/  IXGBE_82599_SCATTER ; 
 int /*<<< orphan*/  IXGBE_CAPS ; 
 int /*<<< orphan*/  IXGBE_CTRL_EXT ; 
 int /*<<< orphan*/  IXGBE_CTRL_EXT_DRV_LOAD ; 
#define  IXGBE_ERR_EEPROM_VERSION 133 
#define  IXGBE_ERR_SFP_NOT_PRESENT 132 
#define  IXGBE_ERR_SFP_NOT_SUPPORTED 131 
 int /*<<< orphan*/  IXGBE_ESDP ; 
 int IXGBE_FEATURE_FAN_FAIL ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_TSO_SIZE ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 void* TRUE ; 
 int /*<<< orphan*/  allow_unsupported_sfp ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_media (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 TYPE_6__* iflib_get_softc_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_set_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_allocate_pci_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_check_fan_failure (struct adapter*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ixgbe_check_wol_support (struct adapter*) ; 
 int /*<<< orphan*/  ixgbe_flow_control ; 
 int /*<<< orphan*/  ixgbe_free_pci_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_init_device_features (struct adapter*) ; 
 scalar_t__ ixgbe_init_shared_code (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_init_swfw_semaphore (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_intr ; 
 int ixgbe_mac_82598EB ; 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_a 129 
#define  ixgbe_mac_X550EM_x 128 
 int ixgbe_reset_hw (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_smart_speed ; 
 int ixgbe_start_hw (struct ixgbe_hw*) ; 
 TYPE_7__ ixgbe_txrx ; 
 scalar_t__ ixgbe_validate_eeprom_checksum (struct ixgbe_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_revid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_subdevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_subvendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_vendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_msix_table_bar (int /*<<< orphan*/ ) ; 
 void* roundup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 

__attribute__((used)) static int
ixgbe_if_attach_pre(if_ctx_t ctx)
{
	struct adapter  *adapter;
	device_t        dev;
	if_softc_ctx_t  scctx;
	struct ixgbe_hw *hw;
	int             error = 0;
	u32             ctrl_ext;

	INIT_DEBUGOUT("ixgbe_attach: begin");

	/* Allocate, clear, and link in our adapter structure */
	dev = iflib_get_dev(ctx);
	adapter = iflib_get_softc(ctx);
	adapter->hw.back = adapter;
	adapter->ctx = ctx;
	adapter->dev = dev;
	scctx = adapter->shared = iflib_get_softc_ctx(ctx);
	adapter->media = iflib_get_media(ctx);
	hw = &adapter->hw;

	/* Determine hardware revision */
	hw->vendor_id = pci_get_vendor(dev);
	hw->device_id = pci_get_device(dev);
	hw->revision_id = pci_get_revid(dev);
	hw->subsystem_vendor_id = pci_get_subvendor(dev);
	hw->subsystem_device_id = pci_get_subdevice(dev);

	/* Do base PCI setup - map BAR0 */
	if (ixgbe_allocate_pci_resources(ctx)) {
		device_printf(dev, "Allocation of PCI resources failed\n");
		return (ENXIO);
	}

	/* let hardware know driver is loaded */
	ctrl_ext = IXGBE_READ_REG(hw, IXGBE_CTRL_EXT);
	ctrl_ext |= IXGBE_CTRL_EXT_DRV_LOAD;
	IXGBE_WRITE_REG(hw, IXGBE_CTRL_EXT, ctrl_ext);

	/*
	 * Initialize the shared code
	 */
	if (ixgbe_init_shared_code(hw) != 0) {
		device_printf(dev, "Unable to initialize the shared code\n");
		error = ENXIO;
		goto err_pci;
	}

	if (hw->mbx.ops.init_params)
		hw->mbx.ops.init_params(hw);

	hw->allow_unsupported_sfp = allow_unsupported_sfp;

	if (hw->mac.type != ixgbe_mac_82598EB)
		hw->phy.smart_speed = ixgbe_smart_speed;

	ixgbe_init_device_features(adapter);

	/* Enable WoL (if supported) */
	ixgbe_check_wol_support(adapter);

	/* Verify adapter fan is still functional (if applicable) */
	if (adapter->feat_en & IXGBE_FEATURE_FAN_FAIL) {
		u32 esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);
		ixgbe_check_fan_failure(adapter, esdp, FALSE);
	}

	/* Ensure SW/FW semaphore is free */
	ixgbe_init_swfw_semaphore(hw);

	/* Set an initial default flow control value */
	hw->fc.requested_mode = ixgbe_flow_control;

	hw->phy.reset_if_overtemp = TRUE;
	error = ixgbe_reset_hw(hw);
	hw->phy.reset_if_overtemp = FALSE;
	if (error == IXGBE_ERR_SFP_NOT_PRESENT) {
		/*
		 * No optics in this port, set up
		 * so the timer routine will probe
		 * for later insertion.
		 */
		adapter->sfp_probe = TRUE;
		error = 0;
	} else if (error == IXGBE_ERR_SFP_NOT_SUPPORTED) {
		device_printf(dev, "Unsupported SFP+ module detected!\n");
		error = EIO;
		goto err_pci;
	} else if (error) {
		device_printf(dev, "Hardware initialization failed\n");
		error = EIO;
		goto err_pci;
	}

	/* Make sure we have a good EEPROM before we read from it */
	if (ixgbe_validate_eeprom_checksum(&adapter->hw, NULL) < 0) {
		device_printf(dev, "The EEPROM Checksum Is Not Valid\n");
		error = EIO;
		goto err_pci;
	}

	error = ixgbe_start_hw(hw);
	switch (error) {
	case IXGBE_ERR_EEPROM_VERSION:
		device_printf(dev, "This device is a pre-production adapter/LOM.  Please be aware there may be issues associated with your hardware.\nIf you are experiencing problems please contact your Intel or hardware representative who provided you with this hardware.\n");
		break;
	case IXGBE_ERR_SFP_NOT_SUPPORTED:
		device_printf(dev, "Unsupported SFP+ Module\n");
		error = EIO;
		goto err_pci;
	case IXGBE_ERR_SFP_NOT_PRESENT:
		device_printf(dev, "No SFP+ Module found\n");
		/* falls thru */
	default:
		break;
	}

	/* Most of the iflib initialization... */

	iflib_set_mac(ctx, hw->mac.addr);
	switch (adapter->hw.mac.type) {
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_X550EM_a:
		scctx->isc_rss_table_size = 512;
		scctx->isc_ntxqsets_max = scctx->isc_nrxqsets_max = 64;
		break;
	default:
		scctx->isc_rss_table_size = 128;
		scctx->isc_ntxqsets_max = scctx->isc_nrxqsets_max = 16;
	}

	/* Allow legacy interrupts */
	ixgbe_txrx.ift_legacy_intr = ixgbe_intr;

	scctx->isc_txqsizes[0] =
	    roundup2(scctx->isc_ntxd[0] * sizeof(union ixgbe_adv_tx_desc) +
	    sizeof(u32), DBA_ALIGN),
	scctx->isc_rxqsizes[0] =
	    roundup2(scctx->isc_nrxd[0] * sizeof(union ixgbe_adv_rx_desc),
	    DBA_ALIGN);

	/* XXX */
	scctx->isc_tx_csum_flags = CSUM_IP | CSUM_TCP | CSUM_UDP | CSUM_TSO |
	    CSUM_IP6_TCP | CSUM_IP6_UDP | CSUM_IP6_TSO;
	if (adapter->hw.mac.type == ixgbe_mac_82598EB) {
		scctx->isc_tx_nsegments = IXGBE_82598_SCATTER;
	} else {
		scctx->isc_tx_csum_flags |= CSUM_SCTP |CSUM_IP6_SCTP;
		scctx->isc_tx_nsegments = IXGBE_82599_SCATTER;
	}

	scctx->isc_msix_bar = pci_msix_table_bar(dev);

	scctx->isc_tx_tso_segments_max = scctx->isc_tx_nsegments;
	scctx->isc_tx_tso_size_max = IXGBE_TSO_SIZE;
	scctx->isc_tx_tso_segsize_max = PAGE_SIZE;

	scctx->isc_txrx = &ixgbe_txrx;

	scctx->isc_capabilities = scctx->isc_capenable = IXGBE_CAPS;

	return (0);

err_pci:
	ctrl_ext = IXGBE_READ_REG(&adapter->hw, IXGBE_CTRL_EXT);
	ctrl_ext &= ~IXGBE_CTRL_EXT_DRV_LOAD;
	IXGBE_WRITE_REG(&adapter->hw, IXGBE_CTRL_EXT, ctrl_ext);
	ixgbe_free_pci_resources(ctx);

	return (error);
}