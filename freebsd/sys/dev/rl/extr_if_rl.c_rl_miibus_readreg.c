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
typedef  int /*<<< orphan*/  uint16_t ;
struct rl_softc {scalar_t__ rl_type; int /*<<< orphan*/  rl_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSR_READ_1 (struct rl_softc*,int const) ; 
 int CSR_READ_2 (struct rl_softc*,int /*<<< orphan*/ ) ; 
#define  MII_ANAR 135 
#define  MII_ANER 134 
#define  MII_ANLPAR 133 
#define  MII_BMCR 132 
#define  MII_BMSR 131 
#define  MII_PHYIDR1 130 
#define  MII_PHYIDR2 129 
 scalar_t__ RL_8139 ; 
 int /*<<< orphan*/  RL_ANAR ; 
 int /*<<< orphan*/  RL_ANER ; 
 int /*<<< orphan*/  RL_BMCR ; 
 int /*<<< orphan*/  RL_BMSR ; 
 int /*<<< orphan*/  RL_LPAR ; 
#define  RL_MEDIASTAT 128 
 struct rl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int mii_bitbang_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rl_mii_bitbang_ops ; 

__attribute__((used)) static int
rl_miibus_readreg(device_t dev, int phy, int reg)
{
	struct rl_softc		*sc;
	uint16_t		rl8139_reg;

	sc = device_get_softc(dev);

	if (sc->rl_type == RL_8139) {
		switch (reg) {
		case MII_BMCR:
			rl8139_reg = RL_BMCR;
			break;
		case MII_BMSR:
			rl8139_reg = RL_BMSR;
			break;
		case MII_ANAR:
			rl8139_reg = RL_ANAR;
			break;
		case MII_ANER:
			rl8139_reg = RL_ANER;
			break;
		case MII_ANLPAR:
			rl8139_reg = RL_LPAR;
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
			return (CSR_READ_1(sc, RL_MEDIASTAT));
		default:
			device_printf(sc->rl_dev, "bad phy register\n");
			return (0);
		}
		return (CSR_READ_2(sc, rl8139_reg));
	}

	return (mii_bitbang_readreg(dev, &rl_mii_bitbang_ops, phy, reg));
}