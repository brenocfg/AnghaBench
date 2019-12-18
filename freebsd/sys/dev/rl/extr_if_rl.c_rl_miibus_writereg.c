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
 int /*<<< orphan*/  CSR_WRITE_2 (struct rl_softc*,int /*<<< orphan*/ ,int) ; 
#define  MII_ANAR 134 
#define  MII_ANER 133 
#define  MII_ANLPAR 132 
#define  MII_BMCR 131 
#define  MII_BMSR 130 
#define  MII_PHYIDR1 129 
#define  MII_PHYIDR2 128 
 scalar_t__ RL_8139 ; 
 int /*<<< orphan*/  RL_ANAR ; 
 int /*<<< orphan*/  RL_ANER ; 
 int /*<<< orphan*/  RL_BMCR ; 
 int /*<<< orphan*/  RL_BMSR ; 
 int /*<<< orphan*/  RL_LPAR ; 
 struct rl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mii_bitbang_writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  rl_mii_bitbang_ops ; 

__attribute__((used)) static int
rl_miibus_writereg(device_t dev, int phy, int reg, int data)
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
			break;
		default:
			device_printf(sc->rl_dev, "bad phy register\n");
			return (0);
		}
		CSR_WRITE_2(sc, rl8139_reg, data);
		return (0);
	}

	mii_bitbang_writereg(dev, &rl_mii_bitbang_ops, phy, reg, data);

	return (0);
}