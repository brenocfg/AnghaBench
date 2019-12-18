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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct iwm_softc {TYPE_1__* cfg; int /*<<< orphan*/  sc_hw_rev; } ;
struct TYPE_2__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_APMG_PS_CTRL_EARLY_PWR_OFF_RESET_DIS ; 
 int /*<<< orphan*/  IWM_APMG_PS_CTRL_REG ; 
 int /*<<< orphan*/  IWM_CSR_HW_IF_CONFIG_REG ; 
 int IWM_CSR_HW_IF_CONFIG_REG_BIT_MAC_SI ; 
 int IWM_CSR_HW_IF_CONFIG_REG_BIT_RADIO_SI ; 
 int IWM_CSR_HW_IF_CONFIG_REG_MSK_MAC_DASH ; 
 int IWM_CSR_HW_IF_CONFIG_REG_MSK_MAC_STEP ; 
 int IWM_CSR_HW_IF_CONFIG_REG_MSK_PHY_DASH ; 
 int IWM_CSR_HW_IF_CONFIG_REG_MSK_PHY_STEP ; 
 int IWM_CSR_HW_IF_CONFIG_REG_MSK_PHY_TYPE ; 
 int IWM_CSR_HW_IF_CONFIG_REG_POS_MAC_DASH ; 
 int IWM_CSR_HW_IF_CONFIG_REG_POS_MAC_STEP ; 
 int IWM_CSR_HW_IF_CONFIG_REG_POS_PHY_DASH ; 
 int IWM_CSR_HW_IF_CONFIG_REG_POS_PHY_STEP ; 
 int IWM_CSR_HW_IF_CONFIG_REG_POS_PHY_TYPE ; 
 int IWM_CSR_HW_REV_DASH (int /*<<< orphan*/ ) ; 
 int IWM_CSR_HW_REV_STEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_DEBUG_RESET ; 
 scalar_t__ IWM_DEVICE_FAMILY_7000 ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int IWM_FW_PHY_CFG_RADIO_DASH ; 
 int IWM_FW_PHY_CFG_RADIO_DASH_POS ; 
 int IWM_FW_PHY_CFG_RADIO_STEP ; 
 int IWM_FW_PHY_CFG_RADIO_STEP_POS ; 
 int IWM_FW_PHY_CFG_RADIO_TYPE ; 
 int IWM_FW_PHY_CFG_RADIO_TYPE_POS ; 
 int /*<<< orphan*/  IWM_WRITE (struct iwm_softc*,int /*<<< orphan*/ ,int) ; 
 int iwm_mvm_get_phy_config (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_set_bits_mask_prph (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iwm_mvm_nic_config(struct iwm_softc *sc)
{
	uint8_t radio_cfg_type, radio_cfg_step, radio_cfg_dash;
	uint32_t reg_val = 0;
	uint32_t phy_config = iwm_mvm_get_phy_config(sc);

	radio_cfg_type = (phy_config & IWM_FW_PHY_CFG_RADIO_TYPE) >>
	    IWM_FW_PHY_CFG_RADIO_TYPE_POS;
	radio_cfg_step = (phy_config & IWM_FW_PHY_CFG_RADIO_STEP) >>
	    IWM_FW_PHY_CFG_RADIO_STEP_POS;
	radio_cfg_dash = (phy_config & IWM_FW_PHY_CFG_RADIO_DASH) >>
	    IWM_FW_PHY_CFG_RADIO_DASH_POS;

	/* SKU control */
	reg_val |= IWM_CSR_HW_REV_STEP(sc->sc_hw_rev) <<
	    IWM_CSR_HW_IF_CONFIG_REG_POS_MAC_STEP;
	reg_val |= IWM_CSR_HW_REV_DASH(sc->sc_hw_rev) <<
	    IWM_CSR_HW_IF_CONFIG_REG_POS_MAC_DASH;

	/* radio configuration */
	reg_val |= radio_cfg_type << IWM_CSR_HW_IF_CONFIG_REG_POS_PHY_TYPE;
	reg_val |= radio_cfg_step << IWM_CSR_HW_IF_CONFIG_REG_POS_PHY_STEP;
	reg_val |= radio_cfg_dash << IWM_CSR_HW_IF_CONFIG_REG_POS_PHY_DASH;

	IWM_WRITE(sc, IWM_CSR_HW_IF_CONFIG_REG,
	    IWM_CSR_HW_IF_CONFIG_REG_MSK_MAC_DASH |
	    IWM_CSR_HW_IF_CONFIG_REG_MSK_MAC_STEP |
	    IWM_CSR_HW_IF_CONFIG_REG_MSK_PHY_STEP |
	    IWM_CSR_HW_IF_CONFIG_REG_MSK_PHY_DASH |
	    IWM_CSR_HW_IF_CONFIG_REG_MSK_PHY_TYPE |
	    IWM_CSR_HW_IF_CONFIG_REG_BIT_RADIO_SI |
	    IWM_CSR_HW_IF_CONFIG_REG_BIT_MAC_SI |
	    reg_val);

	IWM_DPRINTF(sc, IWM_DEBUG_RESET,
	    "Radio type=0x%x-0x%x-0x%x\n", radio_cfg_type,
	    radio_cfg_step, radio_cfg_dash);

	/*
	 * W/A : NIC is stuck in a reset state after Early PCIe power off
	 * (PCIe power is lost before PERST# is asserted), causing ME FW
	 * to lose ownership and not being able to obtain it back.
	 */
	if (sc->cfg->device_family == IWM_DEVICE_FAMILY_7000) {
		iwm_set_bits_mask_prph(sc, IWM_APMG_PS_CTRL_REG,
		    IWM_APMG_PS_CTRL_EARLY_PWR_OFF_RESET_DIS,
		    ~IWM_APMG_PS_CTRL_EARLY_PWR_OFF_RESET_DIS);
	}
}