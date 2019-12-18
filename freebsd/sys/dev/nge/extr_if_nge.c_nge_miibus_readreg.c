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
struct nge_softc {int nge_flags; int /*<<< orphan*/  nge_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BMSR_ACOMP ; 
 int BMSR_ANEG ; 
 int BMSR_EXTCAP ; 
 int BMSR_EXTSTAT ; 
 int BMSR_LINK ; 
 int CSR_READ_4 (struct nge_softc*,int) ; 
#define  MII_ANAR 135 
#define  MII_ANER 134 
#define  MII_ANLPAR 133 
#define  MII_BMCR 132 
#define  MII_BMSR 131 
#define  MII_EXTSR 130 
#define  MII_PHYIDR1 129 
#define  MII_PHYIDR2 128 
 int NGE_FLAG_TBI ; 
 int NGE_TBIBMSR_ANEG_DONE ; 
 int NGE_TBIBMSR_LINKSTAT ; 
 int NGE_TBI_ANAR ; 
 int NGE_TBI_ANER ; 
 int NGE_TBI_ANLPAR ; 
 int NGE_TBI_BMCR ; 
 int NGE_TBI_BMSR ; 
 int NGE_TBI_ESR ; 
 struct nge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int mii_bitbang_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nge_mii_bitbang_ops ; 

__attribute__((used)) static int
nge_miibus_readreg(device_t dev, int phy, int reg)
{
	struct nge_softc *sc;
	int rv;

	sc = device_get_softc(dev);
	if ((sc->nge_flags & NGE_FLAG_TBI) != 0) {
		/* Pretend PHY is at address 0. */
		if (phy != 0)
			return (0);
		switch (reg) {
		case MII_BMCR:
			reg = NGE_TBI_BMCR;
			break;
		case MII_BMSR:
			/* 83820/83821 has different bit layout for BMSR. */
			rv = BMSR_ANEG | BMSR_EXTCAP | BMSR_EXTSTAT;
			reg = CSR_READ_4(sc, NGE_TBI_BMSR);
			if ((reg & NGE_TBIBMSR_ANEG_DONE) != 0)
				rv |= BMSR_ACOMP;
			if ((reg & NGE_TBIBMSR_LINKSTAT) != 0)
				rv |= BMSR_LINK;
			return (rv);
		case MII_ANAR:
			reg = NGE_TBI_ANAR;
			break;
		case MII_ANLPAR:
			reg = NGE_TBI_ANLPAR;
			break;
		case MII_ANER:
			reg = NGE_TBI_ANER;
			break;
		case MII_EXTSR:
			reg = NGE_TBI_ESR;
			break;
		case MII_PHYIDR1:
		case MII_PHYIDR2:
			return (0);
		default:
			device_printf(sc->nge_dev,
			    "bad phy register read : %d\n", reg);
			return (0);
		}
		return (CSR_READ_4(sc, reg));
	}

	return (mii_bitbang_readreg(dev, &nge_mii_bitbang_ops, phy, reg));
}