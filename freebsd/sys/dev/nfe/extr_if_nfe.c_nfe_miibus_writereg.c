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
typedef  int uint32_t ;
struct nfe_softc {int /*<<< orphan*/  nfe_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int NFE_PHYADD_SHIFT ; 
 int NFE_PHY_BUSY ; 
 int /*<<< orphan*/  NFE_PHY_CTL ; 
 int /*<<< orphan*/  NFE_PHY_DATA ; 
 int /*<<< orphan*/  NFE_PHY_STATUS ; 
 int NFE_PHY_WRITE ; 
 int NFE_READ (struct nfe_softc*,int /*<<< orphan*/ ) ; 
 int NFE_TIMEOUT ; 
 int /*<<< orphan*/  NFE_WRITE (struct nfe_softc*,int /*<<< orphan*/ ,int) ; 
 struct nfe_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int nfedebug ; 

__attribute__((used)) static int
nfe_miibus_writereg(device_t dev, int phy, int reg, int val)
{
	struct nfe_softc *sc = device_get_softc(dev);
	uint32_t ctl;
	int ntries;

	NFE_WRITE(sc, NFE_PHY_STATUS, 0xf);

	if (NFE_READ(sc, NFE_PHY_CTL) & NFE_PHY_BUSY) {
		NFE_WRITE(sc, NFE_PHY_CTL, NFE_PHY_BUSY);
		DELAY(100);
	}

	NFE_WRITE(sc, NFE_PHY_DATA, val);
	ctl = NFE_PHY_WRITE | (phy << NFE_PHYADD_SHIFT) | reg;
	NFE_WRITE(sc, NFE_PHY_CTL, ctl);

	for (ntries = 0; ntries < NFE_TIMEOUT; ntries++) {
		DELAY(100);
		if (!(NFE_READ(sc, NFE_PHY_CTL) & NFE_PHY_BUSY))
			break;
	}
#ifdef NFE_DEBUG
	if (nfedebug >= 2 && ntries == NFE_TIMEOUT)
		device_printf(sc->nfe_dev, "could not write to PHY\n");
#endif
	return (0);
}