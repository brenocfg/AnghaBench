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
struct udav_softc {int sc_flags; int /*<<< orphan*/  sc_ue; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDAV_CLRBIT (struct udav_softc*,int /*<<< orphan*/ ,int) ; 
 int UDAV_EXT_PHY ; 
 int /*<<< orphan*/  UDAV_NCR ; 
 int UDAV_NCR_EXT_PHY ; 
 int UDAV_NCR_RST ; 
 int /*<<< orphan*/  UDAV_SETBIT (struct udav_softc*,int /*<<< orphan*/ ,int) ; 
 int UDAV_TX_TIMEOUT ; 
 int hz ; 
 int udav_csr_read1 (struct udav_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ uether_pause (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
udav_reset(struct udav_softc *sc)
{
	int i;

	/* Select PHY */
#if 1
	/*
	 * XXX: force select internal phy.
	 *	external phy routines are not tested.
	 */
	UDAV_CLRBIT(sc, UDAV_NCR, UDAV_NCR_EXT_PHY);
#else
	if (sc->sc_flags & UDAV_EXT_PHY)
		UDAV_SETBIT(sc, UDAV_NCR, UDAV_NCR_EXT_PHY);
	else
		UDAV_CLRBIT(sc, UDAV_NCR, UDAV_NCR_EXT_PHY);
#endif

	UDAV_SETBIT(sc, UDAV_NCR, UDAV_NCR_RST);

	for (i = 0; i < UDAV_TX_TIMEOUT; i++) {
		if (!(udav_csr_read1(sc, UDAV_NCR) & UDAV_NCR_RST))
			break;
		if (uether_pause(&sc->sc_ue, hz / 100))
			break;
	}

	uether_pause(&sc->sc_ue, hz / 100);
}