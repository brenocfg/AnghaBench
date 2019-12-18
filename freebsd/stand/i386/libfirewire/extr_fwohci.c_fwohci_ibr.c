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
typedef  int /*<<< orphan*/  uint32_t ;
struct fwohci_softc {int /*<<< orphan*/ * config_rom; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_PHY_IBR ; 
 int /*<<< orphan*/  FW_PHY_IBR_REG ; 
 int /*<<< orphan*/  FW_PHY_ISBR ; 
 int /*<<< orphan*/  FW_PHY_ISBR_REG ; 
 int /*<<< orphan*/  OHCI_BUS_OPT ; 
 int /*<<< orphan*/  OHCI_CROMHDR ; 
 int /*<<< orphan*/  OWRITE (struct fwohci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fwphy_rddata (struct fwohci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwphy_wrdata (struct fwohci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

void
fwohci_ibr(struct fwohci_softc *sc)
{
	uint32_t fun;

	device_printf(sc->dev, "Initiate bus reset\n");

	/*
	 * Make sure our cached values from the config rom are
	 * initialised.
	 */
	OWRITE(sc, OHCI_CROMHDR, ntohl(sc->config_rom[0]));
	OWRITE(sc, OHCI_BUS_OPT, ntohl(sc->config_rom[2]));

	/*
	 * Set root hold-off bit so that non cyclemaster capable node
	 * shouldn't became the root node.
	 */
#if 1
	fun = fwphy_rddata(sc, FW_PHY_IBR_REG);
	fun |= FW_PHY_IBR;
	fun = fwphy_wrdata(sc, FW_PHY_IBR_REG, fun);
#else	/* Short bus reset */
	fun = fwphy_rddata(sc, FW_PHY_ISBR_REG);
	fun |= FW_PHY_ISBR;
	fun = fwphy_wrdata(sc, FW_PHY_ISBR_REG, fun);
#endif
}