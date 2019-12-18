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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct ahci_controller {int numirqs; int /*<<< orphan*/ * r_mem; scalar_t__ r_rid; scalar_t__ subdeviceid; scalar_t__ subvendorid; scalar_t__ deviceid; scalar_t__ vendorid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_CAP ; 
 int AHCI_CAP_SSS ; 
 int /*<<< orphan*/  AHCI_PI ; 
 int ATA_INL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IOMUX_GPR13 ; 
 int IOMUX_GPR13_SATA_PHY_0 (int) ; 
 int IOMUX_GPR13_SATA_PHY_1 (int) ; 
 int IOMUX_GPR13_SATA_PHY_2 (int) ; 
 int IOMUX_GPR13_SATA_PHY_3 (int) ; 
 int IOMUX_GPR13_SATA_PHY_4 (int) ; 
 int IOMUX_GPR13_SATA_PHY_5 (int) ; 
 int IOMUX_GPR13_SATA_PHY_6 (int) ; 
 int IOMUX_GPR13_SATA_PHY_7 (int) ; 
 int IOMUX_GPR13_SATA_PHY_8 (int) ; 
 int IOMUX_GPR13_SATA_SPEED (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SATA_PHY_CLOCK_RESET ; 
 int /*<<< orphan*/  SATA_PHY_CLOCK_RESET_RST ; 
 int /*<<< orphan*/  SATA_PHY_LANE0_OUT_STAT ; 
 int SATA_PHY_LANE0_OUT_STAT_RX_PLL_STATE ; 
 int /*<<< orphan*/  SATA_TIMER1MS ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int ahci_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 struct ahci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int imx6_ahci_phy_read (struct ahci_controller*,int /*<<< orphan*/ ,int*) ; 
 int imx6_ahci_phy_write (struct ahci_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int imx6_ccm_sata_enable () ; 
 int imx_ccm_ahb_hz () ; 
 int imx_iomux_gpr_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_iomux_gpr_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
imx6_ahci_attach(device_t dev)
{
	struct ahci_controller* ctlr;
	uint16_t pllstat;
	uint32_t v;
	int error, timeout;

	ctlr = device_get_softc(dev);

	/* Power up the controller and phy. */
	error = imx6_ccm_sata_enable();
	if (error != 0) {
		device_printf(dev, "error enabling controller and phy\n");
		return (error);
	}

	ctlr->vendorid = 0;
	ctlr->deviceid = 0;
	ctlr->subvendorid = 0;
	ctlr->subdeviceid = 0;
	ctlr->numirqs = 1;
	ctlr->r_rid = 0;
	if ((ctlr->r_mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &ctlr->r_rid, RF_ACTIVE)) == NULL) {
		return (ENXIO);
	}

	v = imx_iomux_gpr_get(IOMUX_GPR13);
	/* Clear out existing values; these numbers are bitmasks. */
	v &= ~(IOMUX_GPR13_SATA_PHY_8(7) 	|
	       IOMUX_GPR13_SATA_PHY_7(0x1f) 	|
	       IOMUX_GPR13_SATA_PHY_6(7) 	|
	       IOMUX_GPR13_SATA_SPEED(1) 	|
	       IOMUX_GPR13_SATA_PHY_5(1) 	|
	       IOMUX_GPR13_SATA_PHY_4(7) 	|
	       IOMUX_GPR13_SATA_PHY_3(0xf) 	|
	       IOMUX_GPR13_SATA_PHY_2(0x1f) 	|
	       IOMUX_GPR13_SATA_PHY_1(1) 	|
	       IOMUX_GPR13_SATA_PHY_0(1));
	/* setting */
	v |= IOMUX_GPR13_SATA_PHY_8(5) 		|     /* Rx 3.0db */
	     IOMUX_GPR13_SATA_PHY_7(0x12) 	|     /* Rx SATA2m */
	     IOMUX_GPR13_SATA_PHY_6(3) 		|     /* Rx DPLL mode */
	     IOMUX_GPR13_SATA_SPEED(1) 		|     /* 3.0GHz */
	     IOMUX_GPR13_SATA_PHY_5(0) 		|     /* SpreadSpectram */
	     IOMUX_GPR13_SATA_PHY_4(4) 		|     /* Tx Attenuation 9/16 */
	     IOMUX_GPR13_SATA_PHY_3(0) 		|     /* Tx Boost 0db */
	     IOMUX_GPR13_SATA_PHY_2(0x11) 	|     /* Tx Level 1.104V */
	     IOMUX_GPR13_SATA_PHY_1(1);               /* PLL clock enable */
	imx_iomux_gpr_set(IOMUX_GPR13, v);

	/* phy reset */
	error = imx6_ahci_phy_write(ctlr, SATA_PHY_CLOCK_RESET,
	    SATA_PHY_CLOCK_RESET_RST);
	if (error != 0) {
		device_printf(dev, "cannot reset PHY\n");
		goto fail;
	}

	for (timeout = 50; timeout > 0; --timeout) {
		DELAY(100);
		error = imx6_ahci_phy_read(ctlr, SATA_PHY_LANE0_OUT_STAT,
		    &pllstat);
		if (error != 0) {
			device_printf(dev, "cannot read LANE0 status\n");
			goto fail;
		}
		if (pllstat & SATA_PHY_LANE0_OUT_STAT_RX_PLL_STATE) {
			break;
		}
	}
	if (timeout <= 0) {
		device_printf(dev, "time out reading LANE0 status\n");
		error = ETIMEDOUT;
		goto fail;
	}

	/* Support Staggered Spin-up */
	v = ATA_INL(ctlr->r_mem, AHCI_CAP);
	ATA_OUTL(ctlr->r_mem, AHCI_CAP, v | AHCI_CAP_SSS);

	/* Ports Implemented. must set 1 */
	v = ATA_INL(ctlr->r_mem, AHCI_PI);
	ATA_OUTL(ctlr->r_mem, AHCI_PI, v | (1 << 0));

	/* set 1ms-timer = AHB clock / 1000 */
	ATA_OUTL(ctlr->r_mem, SATA_TIMER1MS,
		 imx_ccm_ahb_hz() / 1000);

	/*
	 * Note: ahci_attach will release ctlr->r_mem on errors automatically
	 */
	return (ahci_attach(dev));

fail:
	bus_release_resource(dev, SYS_RES_MEMORY, ctlr->r_rid, ctlr->r_mem);
	return (error);
}