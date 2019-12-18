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
typedef  int u_int ;
struct mii_softc {int mii_flags; } ;

/* Variables and functions */
 int ANAR_PAUSE_ASYM ; 
 int ANAR_PAUSE_SYM ; 
#define  ANLPAR_PAUSE_ASYM 129 
#define  ANLPAR_PAUSE_NONE 128 
 int ANLPAR_PAUSE_SYM ; 
 int ANLPAR_PAUSE_TOWARDS ; 
 int IFM_ETH_RXPAUSE ; 
 int IFM_ETH_TXPAUSE ; 
 int IFM_FLOW ; 
 int MIIF_DOPAUSE ; 
 int MIIF_IS_1000X ; 
 int /*<<< orphan*/  MII_ANAR ; 
 int /*<<< orphan*/  MII_ANLPAR ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 

u_int
mii_phy_flowstatus(struct mii_softc *sc)
{
	int anar, anlpar;

	if ((sc->mii_flags & MIIF_DOPAUSE) == 0)
		return (0);

	anar = PHY_READ(sc, MII_ANAR);
	anlpar = PHY_READ(sc, MII_ANLPAR);

	/*
	 * Check for 1000BASE-X.  Autonegotiation is a bit
	 * different on such devices.
	 */
	if ((sc->mii_flags & MIIF_IS_1000X) != 0) {
		anar <<= 3;
		anlpar <<= 3;
	}

	if ((anar & ANAR_PAUSE_SYM) != 0 && (anlpar & ANLPAR_PAUSE_SYM) != 0)
		return (IFM_FLOW | IFM_ETH_TXPAUSE | IFM_ETH_RXPAUSE);

	if ((anar & ANAR_PAUSE_SYM) == 0) {
		if ((anar & ANAR_PAUSE_ASYM) != 0 &&
		    (anlpar & ANLPAR_PAUSE_TOWARDS) != 0)
			return (IFM_FLOW | IFM_ETH_TXPAUSE);
		else
			return (0);
	}

	if ((anar & ANAR_PAUSE_ASYM) == 0) {
		if ((anlpar & ANLPAR_PAUSE_SYM) != 0)
			return (IFM_FLOW | IFM_ETH_TXPAUSE | IFM_ETH_RXPAUSE);
		else
			return (0);
	}

	switch ((anlpar & ANLPAR_PAUSE_TOWARDS)) {
	case ANLPAR_PAUSE_NONE:
		return (0);
	case ANLPAR_PAUSE_ASYM:
		return (IFM_FLOW | IFM_ETH_RXPAUSE);
	default:
		return (IFM_FLOW | IFM_ETH_RXPAUSE | IFM_ETH_TXPAUSE);
	}
	/* NOTREACHED */
}