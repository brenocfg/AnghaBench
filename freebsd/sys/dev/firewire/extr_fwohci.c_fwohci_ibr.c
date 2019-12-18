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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * config_rom; } ;
struct fwohci_softc {TYPE_1__ fc; } ;
struct firewire_comm {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_GLOCK (struct firewire_comm*) ; 
 int /*<<< orphan*/  FW_GUNLOCK (struct firewire_comm*) ; 
 int FW_PHY_IBR ; 
 int /*<<< orphan*/  FW_PHY_IBR_REG ; 
 int FW_PHY_ISBR ; 
 int /*<<< orphan*/  FW_PHY_ISBR_REG ; 
 int FW_PHY_RHB ; 
 int /*<<< orphan*/  OHCI_BUS_OPT ; 
 int /*<<< orphan*/  OHCI_CROMHDR ; 
 int /*<<< orphan*/  OWRITE (struct fwohci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int fwphy_rddata (struct fwohci_softc*,int /*<<< orphan*/ ) ; 
 int fwphy_wrdata (struct fwohci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

void
fwohci_ibr(struct firewire_comm *fc)
{
	struct fwohci_softc *sc;
	uint32_t fun;

	device_printf(fc->dev, "Initiate bus reset\n");
	sc = (struct fwohci_softc *)fc;

	FW_GLOCK(fc);
	/*
	 * Make sure our cached values from the config rom are
	 * initialised.
	 */
	OWRITE(sc, OHCI_CROMHDR, ntohl(sc->fc.config_rom[0]));
	OWRITE(sc, OHCI_BUS_OPT, ntohl(sc->fc.config_rom[2]));

	/*
	 * Set root hold-off bit so that non cyclemaster capable node
	 * shouldn't became the root node.
	 */
#if 1
	fun = fwphy_rddata(sc, FW_PHY_IBR_REG);
	fun |= FW_PHY_IBR | FW_PHY_RHB;
	fun = fwphy_wrdata(sc, FW_PHY_IBR_REG, fun);
#else	/* Short bus reset */
	fun = fwphy_rddata(sc, FW_PHY_ISBR_REG);
	fun |= FW_PHY_ISBR | FW_PHY_RHB;
	fun = fwphy_wrdata(sc, FW_PHY_ISBR_REG, fun);
#endif
	FW_GUNLOCK(fc);
}