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
typedef  int uint32_t ;
struct omap_uhh_softc {int uhh_rev; int* port_mode; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
#define  EHCI_HCD_OMAP_MODE_HSIC 131 
#define  EHCI_HCD_OMAP_MODE_PHY 130 
#define  EHCI_HCD_OMAP_MODE_TLL 129 
#define  EHCI_HCD_OMAP_MODE_UNKNOWN 128 
 int /*<<< orphan*/  EXT_CLK ; 
 int OMAP_HS_USB_PORTS ; 
 scalar_t__ OMAP_UHH_REV1 ; 
 scalar_t__ OMAP_UHH_REV2 ; 
 int /*<<< orphan*/  OMAP_USBHOST_INSNREG04 ; 
 int OMAP_USBHOST_INSNREG04_DISABLE_UNSUSPEND ; 
 int /*<<< orphan*/  OMAP_USBHOST_UHH_HOSTCONFIG ; 
 int /*<<< orphan*/  OMAP_USBHOST_UHH_REVISION ; 
 int /*<<< orphan*/  OMAP_USBHOST_UHH_SYSCONFIG ; 
 int UHH_HOSTCONFIG_APP_START_CLK ; 
 int UHH_HOSTCONFIG_ENA_INCR16 ; 
 int UHH_HOSTCONFIG_ENA_INCR4 ; 
 int UHH_HOSTCONFIG_ENA_INCR8 ; 
 int UHH_HOSTCONFIG_ENA_INCR_ALIGN ; 
 int UHH_HOSTCONFIG_P1_CONNECT_STATUS ; 
 int UHH_HOSTCONFIG_P1_MODE_HSIC ; 
 int UHH_HOSTCONFIG_P1_MODE_MASK ; 
 int UHH_HOSTCONFIG_P1_MODE_UTMI_PHY ; 
 int UHH_HOSTCONFIG_P1_ULPI_BYPASS ; 
 int UHH_HOSTCONFIG_P2_CONNECT_STATUS ; 
 int UHH_HOSTCONFIG_P2_MODE_HSIC ; 
 int UHH_HOSTCONFIG_P2_MODE_MASK ; 
 int UHH_HOSTCONFIG_P2_MODE_UTMI_PHY ; 
 int UHH_HOSTCONFIG_P3_CONNECT_STATUS ; 
 int UHH_SYSCONFIG_AUTOIDLE ; 
 int UHH_SYSCONFIG_CLOCKACTIVITY ; 
 int UHH_SYSCONFIG_ENAWAKEUP ; 
 int UHH_SYSCONFIG_IDLEMODE_MASK ; 
 int UHH_SYSCONFIG_IDLEMODE_NOIDLE ; 
 int UHH_SYSCONFIG_MIDLEMODE_MASK ; 
 int UHH_SYSCONFIG_MIDLEMODE_SMARTSTANDBY ; 
 int UHH_SYSCONFIG_SIDLEMODE_MASK ; 
 int UHH_SYSCONFIG_SIDLEMODE_SMARTIDLE ; 
 int UHH_SYSCONFIG_STANDBYMODE_MASK ; 
 int UHH_SYSCONFIG_STANDBYMODE_NOSTDBY ; 
 int /*<<< orphan*/  USBHSHOST_CLK ; 
 int /*<<< orphan*/  USBP1_HSIC_CLK ; 
 int /*<<< orphan*/  USBP1_PHY_CLK ; 
 int /*<<< orphan*/  USBP1_UTMI_CLK ; 
 int /*<<< orphan*/  USBP2_HSIC_CLK ; 
 int /*<<< orphan*/  USBP2_PHY_CLK ; 
 int /*<<< orphan*/  USBP2_UTMI_CLK ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  omap_tll_utmi_enable (int) ; 
 void* omap_uhh_read_4 (struct omap_uhh_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_uhh_write_4 (struct omap_uhh_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ti_prcm_clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_prcm_clk_set_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
omap_uhh_init(struct omap_uhh_softc *isc)
{
	uint8_t tll_ch_mask;
	uint32_t reg;
	int i;

	/* Enable Clocks for high speed USBHOST */
	ti_prcm_clk_enable(USBHSHOST_CLK);

	/* Read the UHH revision */
	isc->uhh_rev = omap_uhh_read_4(isc, OMAP_USBHOST_UHH_REVISION);
	device_printf(isc->sc_dev, "UHH revision 0x%08x\n", isc->uhh_rev);

	if (isc->uhh_rev == OMAP_UHH_REV2) {
		/* For OMAP44xx devices you have to enable the per-port clocks:
		 *  PHY_MODE  - External ULPI clock
		 *  TTL_MODE  - Internal UTMI clock
		 *  HSIC_MODE - Internal 480Mhz and 60Mhz clocks
		 */
		switch(isc->port_mode[0]) {
		case EHCI_HCD_OMAP_MODE_UNKNOWN:
			break;
		case EHCI_HCD_OMAP_MODE_PHY:
			if (ti_prcm_clk_set_source(USBP1_PHY_CLK, EXT_CLK))
				device_printf(isc->sc_dev,
				    "failed to set clock source for port 0\n");
			if (ti_prcm_clk_enable(USBP1_PHY_CLK))
				device_printf(isc->sc_dev,
				    "failed to set clock USBP1_PHY_CLK source for port 0\n");
			break;
		case EHCI_HCD_OMAP_MODE_TLL:
			if (ti_prcm_clk_enable(USBP1_UTMI_CLK))
				device_printf(isc->sc_dev,
				    "failed to set clock USBP1_PHY_CLK source for port 0\n");
			break;
		case EHCI_HCD_OMAP_MODE_HSIC:
			if (ti_prcm_clk_enable(USBP1_HSIC_CLK))
				device_printf(isc->sc_dev,
				    "failed to set clock USBP1_PHY_CLK source for port 0\n");
			break;
		default:
			device_printf(isc->sc_dev, "unknown port mode %d for port 0\n", isc->port_mode[0]);
		}
		switch(isc->port_mode[1]) {
		case EHCI_HCD_OMAP_MODE_UNKNOWN:
			break;
		case EHCI_HCD_OMAP_MODE_PHY:
			if (ti_prcm_clk_set_source(USBP2_PHY_CLK, EXT_CLK))
				device_printf(isc->sc_dev,
				    "failed to set clock source for port 0\n");
			if (ti_prcm_clk_enable(USBP2_PHY_CLK))
				device_printf(isc->sc_dev,
				    "failed to set clock USBP2_PHY_CLK source for port 1\n");
			break;
		case EHCI_HCD_OMAP_MODE_TLL:
			if (ti_prcm_clk_enable(USBP2_UTMI_CLK))
				device_printf(isc->sc_dev,
				    "failed to set clock USBP2_UTMI_CLK source for port 1\n");
			break;
		case EHCI_HCD_OMAP_MODE_HSIC:
			if (ti_prcm_clk_enable(USBP2_HSIC_CLK))
				device_printf(isc->sc_dev,
				    "failed to set clock USBP2_HSIC_CLK source for port 1\n");
			break;
		default:
			device_printf(isc->sc_dev, "unknown port mode %d for port 1\n", isc->port_mode[1]);
		}
	}

	/* Put UHH in SmartIdle/SmartStandby mode */
	reg = omap_uhh_read_4(isc, OMAP_USBHOST_UHH_SYSCONFIG);
	if (isc->uhh_rev == OMAP_UHH_REV1) {
		reg &= ~(UHH_SYSCONFIG_SIDLEMODE_MASK |
		    UHH_SYSCONFIG_MIDLEMODE_MASK);
		reg |= (UHH_SYSCONFIG_ENAWAKEUP |
		    UHH_SYSCONFIG_AUTOIDLE |
		    UHH_SYSCONFIG_CLOCKACTIVITY |
		    UHH_SYSCONFIG_SIDLEMODE_SMARTIDLE |
		    UHH_SYSCONFIG_MIDLEMODE_SMARTSTANDBY);
	} else if (isc->uhh_rev == OMAP_UHH_REV2) {
		reg &= ~UHH_SYSCONFIG_IDLEMODE_MASK;
		reg |=  UHH_SYSCONFIG_IDLEMODE_NOIDLE;
		reg &= ~UHH_SYSCONFIG_STANDBYMODE_MASK;
		reg |=  UHH_SYSCONFIG_STANDBYMODE_NOSTDBY;
	}
	omap_uhh_write_4(isc, OMAP_USBHOST_UHH_SYSCONFIG, reg);
	device_printf(isc->sc_dev, "OMAP_UHH_SYSCONFIG: 0x%08x\n", reg);

	reg = omap_uhh_read_4(isc, OMAP_USBHOST_UHH_HOSTCONFIG);

	/* Setup ULPI bypass and burst configurations */
	reg |= (UHH_HOSTCONFIG_ENA_INCR4 |
			UHH_HOSTCONFIG_ENA_INCR8 |
			UHH_HOSTCONFIG_ENA_INCR16);
	reg &= ~UHH_HOSTCONFIG_ENA_INCR_ALIGN;

	if (isc->uhh_rev == OMAP_UHH_REV1) {
		if (isc->port_mode[0] == EHCI_HCD_OMAP_MODE_UNKNOWN)
			reg &= ~UHH_HOSTCONFIG_P1_CONNECT_STATUS;
		if (isc->port_mode[1] == EHCI_HCD_OMAP_MODE_UNKNOWN)
			reg &= ~UHH_HOSTCONFIG_P2_CONNECT_STATUS;
		if (isc->port_mode[2] == EHCI_HCD_OMAP_MODE_UNKNOWN)
			reg &= ~UHH_HOSTCONFIG_P3_CONNECT_STATUS;

		/* Bypass the TLL module for PHY mode operation */
		if ((isc->port_mode[0] == EHCI_HCD_OMAP_MODE_PHY) ||
		    (isc->port_mode[1] == EHCI_HCD_OMAP_MODE_PHY) ||
		    (isc->port_mode[2] == EHCI_HCD_OMAP_MODE_PHY))
			reg &= ~UHH_HOSTCONFIG_P1_ULPI_BYPASS;
		else
			reg |= UHH_HOSTCONFIG_P1_ULPI_BYPASS;

	} else if (isc->uhh_rev == OMAP_UHH_REV2) {
		reg |=  UHH_HOSTCONFIG_APP_START_CLK;

		/* Clear port mode fields for PHY mode*/
		reg &= ~UHH_HOSTCONFIG_P1_MODE_MASK;
		reg &= ~UHH_HOSTCONFIG_P2_MODE_MASK;

		if (isc->port_mode[0] == EHCI_HCD_OMAP_MODE_TLL)
			reg |= UHH_HOSTCONFIG_P1_MODE_UTMI_PHY;
		else if (isc->port_mode[0] == EHCI_HCD_OMAP_MODE_HSIC)
			reg |= UHH_HOSTCONFIG_P1_MODE_HSIC;

		if (isc->port_mode[1] == EHCI_HCD_OMAP_MODE_TLL)
			reg |= UHH_HOSTCONFIG_P2_MODE_UTMI_PHY;
		else if (isc->port_mode[1] == EHCI_HCD_OMAP_MODE_HSIC)
			reg |= UHH_HOSTCONFIG_P2_MODE_HSIC;
	}

	omap_uhh_write_4(isc, OMAP_USBHOST_UHH_HOSTCONFIG, reg);
	device_printf(isc->sc_dev, "UHH setup done, uhh_hostconfig=0x%08x\n", reg);


	/* I found the code and comments in the Linux EHCI driver - thanks guys :)
	 *
	 * "An undocumented "feature" in the OMAP3 EHCI controller, causes suspended
	 * ports to be taken out of suspend when the USBCMD.Run/Stop bit is cleared
	 * (for example when we do omap_uhh_bus_suspend). This breaks suspend-resume if
	 * the root-hub is allowed to suspend. Writing 1 to this undocumented
	 * register bit disables this feature and restores normal behavior."
	 */
#if 0
	omap_uhh_write_4(isc, OMAP_USBHOST_INSNREG04,
	    OMAP_USBHOST_INSNREG04_DISABLE_UNSUSPEND);
#endif
	tll_ch_mask = 0;
	for (i = 0; i < OMAP_HS_USB_PORTS; i++) {
		if (isc->port_mode[i] == EHCI_HCD_OMAP_MODE_TLL)
			tll_ch_mask |= (1 << i);
	}
	if (tll_ch_mask)
		omap_tll_utmi_enable(tll_ch_mask);

	return(0);
}