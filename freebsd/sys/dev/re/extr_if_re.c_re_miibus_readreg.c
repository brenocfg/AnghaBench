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
typedef  int u_int16_t ;
struct rl_softc {scalar_t__ rl_type; int /*<<< orphan*/  rl_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BMCR_ISO ; 
 int BMCR_LOOP ; 
 int CSR_READ_1 (struct rl_softc*,int const) ; 
 int CSR_READ_2 (struct rl_softc*,int) ; 
#define  MII_ANAR 135 
#define  MII_ANER 134 
#define  MII_ANLPAR 133 
#define  MII_BMCR 132 
#define  MII_BMSR 131 
#define  MII_PHYIDR1 130 
#define  MII_PHYIDR2 129 
 scalar_t__ RL_8139CPLUS ; 
 scalar_t__ RL_8169 ; 
 int RL_ANAR ; 
 int RL_ANER ; 
 int RL_BMCR ; 
 int RL_BMSR ; 
 int RL_LPAR ; 
#define  RL_MEDIASTAT 128 
 struct rl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int re_gmii_readreg (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
re_miibus_readreg(device_t dev, int phy, int reg)
{
	struct rl_softc		*sc;
	u_int16_t		rval = 0;
	u_int16_t		re8139_reg = 0;

	sc = device_get_softc(dev);

	if (sc->rl_type == RL_8169) {
		rval = re_gmii_readreg(dev, phy, reg);
		return (rval);
	}

	switch (reg) {
	case MII_BMCR:
		re8139_reg = RL_BMCR;
		break;
	case MII_BMSR:
		re8139_reg = RL_BMSR;
		break;
	case MII_ANAR:
		re8139_reg = RL_ANAR;
		break;
	case MII_ANER:
		re8139_reg = RL_ANER;
		break;
	case MII_ANLPAR:
		re8139_reg = RL_LPAR;
		break;
	case MII_PHYIDR1:
	case MII_PHYIDR2:
		return (0);
	/*
	 * Allow the rlphy driver to read the media status
	 * register. If we have a link partner which does not
	 * support NWAY, this is the register which will tell
	 * us the results of parallel detection.
	 */
	case RL_MEDIASTAT:
		rval = CSR_READ_1(sc, RL_MEDIASTAT);
		return (rval);
	default:
		device_printf(sc->rl_dev, "bad phy register\n");
		return (0);
	}
	rval = CSR_READ_2(sc, re8139_reg);
	if (sc->rl_type == RL_8139CPLUS && re8139_reg == RL_BMCR) {
		/* 8139C+ has different bit layout. */
		rval &= ~(BMCR_LOOP | BMCR_ISO);
	}
	return (rval);
}