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
typedef  int uint16_t ;
struct mii_softc {int /*<<< orphan*/  mii_dev; } ;

/* Variables and functions */
 int CIPHY_10BTCSR_ECHO ; 
 int CIPHY_AUXCSR_FDX ; 
 int CIPHY_AUXCSR_MDPPS ; 
 int CIPHY_AUXCSR_SPEED ; 
 int CIPHY_ECTL1_INTSEL ; 
 int CIPHY_ECTL1_IOVOL ; 
 int CIPHY_INTSEL_RGMII ; 
 int CIPHY_IOVOL_2500MV ; 
 int CIPHY_LED_LINKACTBLINK ; 
 int /*<<< orphan*/  CIPHY_MII_10BTCSR ; 
 int /*<<< orphan*/  CIPHY_MII_AUXCSR ; 
 int /*<<< orphan*/  CIPHY_MII_ECTL1 ; 
 int /*<<< orphan*/  CIPHY_MII_LED ; 
 int /*<<< orphan*/  CIPHY_MII_PHYIDR2 ; 
 int CIPHY_SPEED10 ; 
 int CIPHY_SPEED100 ; 
 int MII_MODEL (int) ; 
#define  MII_MODEL_xxCICADA_CS8201 136 
#define  MII_MODEL_xxCICADA_CS8201A 135 
#define  MII_MODEL_xxCICADA_CS8201B 134 
#define  MII_MODEL_xxCICADA_CS8204 133 
#define  MII_MODEL_xxCICADA_CS8244 132 
#define  MII_MODEL_xxCICADA_VSC8211 131 
#define  MII_MODEL_xxCICADA_VSC8221 130 
#define  MII_MODEL_xxVITESSE_VSC8601 129 
#define  MII_MODEL_xxVITESSE_VSC8641 128 
 int /*<<< orphan*/  PHY_CLRBIT (struct mii_softc*,int /*<<< orphan*/ ,int) ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_SETBIT (struct mii_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ mii_phy_mac_match (struct mii_softc*,char*) ; 

__attribute__((used)) static void
ciphy_fixup(struct mii_softc *sc)
{
	uint16_t		model;
	uint16_t		status, speed;
	uint16_t		val;

	model = MII_MODEL(PHY_READ(sc, CIPHY_MII_PHYIDR2));
	status = PHY_READ(sc, CIPHY_MII_AUXCSR);
	speed = status & CIPHY_AUXCSR_SPEED;

	if (mii_phy_mac_match(sc, "nfe")) {
		/* need to set for 2.5V RGMII for NVIDIA adapters */
		val = PHY_READ(sc, CIPHY_MII_ECTL1);
		val &= ~(CIPHY_ECTL1_IOVOL | CIPHY_ECTL1_INTSEL);
		val |= (CIPHY_IOVOL_2500MV | CIPHY_INTSEL_RGMII);
		PHY_WRITE(sc, CIPHY_MII_ECTL1, val);
		/* From Linux. */
		val = PHY_READ(sc, CIPHY_MII_AUXCSR);
		val |= CIPHY_AUXCSR_MDPPS;
		PHY_WRITE(sc, CIPHY_MII_AUXCSR, val);
		val = PHY_READ(sc, CIPHY_MII_10BTCSR);
		val |= CIPHY_10BTCSR_ECHO;
		PHY_WRITE(sc, CIPHY_MII_10BTCSR, val);
	}

	switch (model) {
	case MII_MODEL_xxCICADA_CS8204:
	case MII_MODEL_xxCICADA_CS8201:

		/* Turn off "aux mode" (whatever that means) */
		PHY_SETBIT(sc, CIPHY_MII_AUXCSR, CIPHY_AUXCSR_MDPPS);

		/*
		 * Work around speed polling bug in VT3119/VT3216
		 * when using MII in full duplex mode.
		 */
		if ((speed == CIPHY_SPEED10 || speed == CIPHY_SPEED100) &&
		    (status & CIPHY_AUXCSR_FDX)) {
			PHY_SETBIT(sc, CIPHY_MII_10BTCSR, CIPHY_10BTCSR_ECHO);
		} else {
			PHY_CLRBIT(sc, CIPHY_MII_10BTCSR, CIPHY_10BTCSR_ECHO);
		}

		/* Enable link/activity LED blink. */
		PHY_SETBIT(sc, CIPHY_MII_LED, CIPHY_LED_LINKACTBLINK);

		break;

	case MII_MODEL_xxCICADA_CS8201A:
	case MII_MODEL_xxCICADA_CS8201B:

		/*
		 * Work around speed polling bug in VT3119/VT3216
		 * when using MII in full duplex mode.
		 */
		if ((speed == CIPHY_SPEED10 || speed == CIPHY_SPEED100) &&
		    (status & CIPHY_AUXCSR_FDX)) {
			PHY_SETBIT(sc, CIPHY_MII_10BTCSR, CIPHY_10BTCSR_ECHO);
		} else {
			PHY_CLRBIT(sc, CIPHY_MII_10BTCSR, CIPHY_10BTCSR_ECHO);
		}

		break;
	case MII_MODEL_xxCICADA_VSC8211:
	case MII_MODEL_xxCICADA_VSC8221:
	case MII_MODEL_xxCICADA_CS8244:
	case MII_MODEL_xxVITESSE_VSC8601:
	case MII_MODEL_xxVITESSE_VSC8641:
		break;
	default:
		device_printf(sc->mii_dev, "unknown CICADA PHY model %x\n",
		    model);
		break;
	}
}