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
typedef  scalar_t__ uint32_t ;
struct ffec_softc {int fectype; int phy_conn_type; } ;

/* Variables and functions */
#define  FECTYPE_IMX53 130 
 int /*<<< orphan*/  FEC_MIIGSK_CFGR ; 
 scalar_t__ FEC_MIIGSK_CFGR_IF_MODE_RMII ; 
 int /*<<< orphan*/  FEC_MIIGSK_ENR ; 
 scalar_t__ FEC_MIIGSK_ENR_EN ; 
 int FEC_MIIGSK_ENR_READY ; 
#define  MII_CONTYPE_MII 129 
#define  MII_CONTYPE_RMII 128 
 int RD2 (struct ffec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR2 (struct ffec_softc*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
ffec_miigasket_setup(struct ffec_softc *sc)
{
	uint32_t ifmode;

	/*
	 * We only need the gasket for MII and RMII connections on certain SoCs.
	 */

	switch (sc->fectype)
	{
	case FECTYPE_IMX53:
		break;
	default:
		return;
	}

	switch (sc->phy_conn_type)
	{
	case MII_CONTYPE_MII:
		ifmode = 0;
		break;
	case MII_CONTYPE_RMII:
		ifmode = FEC_MIIGSK_CFGR_IF_MODE_RMII;
		break;
	default:
		return;
	}

	/*
	 * Disable the gasket, configure for either MII or RMII, then enable.
	 */

	WR2(sc, FEC_MIIGSK_ENR, 0);
	while (RD2(sc, FEC_MIIGSK_ENR) & FEC_MIIGSK_ENR_READY)
		continue;

	WR2(sc, FEC_MIIGSK_CFGR, ifmode);

	WR2(sc, FEC_MIIGSK_ENR, FEC_MIIGSK_ENR_EN);
	while (!(RD2(sc, FEC_MIIGSK_ENR) & FEC_MIIGSK_ENR_READY))
		continue;
}