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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct udav_softc {int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int,int,int) ; 
 int /*<<< orphan*/  UDAV_CLRBIT (struct udav_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UDAV_EPAR ; 
 int UDAV_EPAR_EROA_MASK ; 
 int UDAV_EPAR_PHY_ADR0 ; 
 int /*<<< orphan*/  UDAV_EPCR ; 
 int UDAV_EPCR_EPOS ; 
 int UDAV_EPCR_ERPRR ; 
 int /*<<< orphan*/  UDAV_EPDRL ; 
 int /*<<< orphan*/  UDAV_LOCK (struct udav_softc*) ; 
 int /*<<< orphan*/  UDAV_UNLOCK (struct udav_softc*) ; 
 struct udav_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udav_csr_read (struct udav_softc*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  udav_csr_write1 (struct udav_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
udav_miibus_readreg(device_t dev, int phy, int reg)
{
	struct udav_softc *sc = device_get_softc(dev);
	uint16_t data16;
	uint8_t val[2];
	int locked;

	/* XXX: one PHY only for the internal PHY */
	if (phy != 0)
		return (0);

	locked = mtx_owned(&sc->sc_mtx);
	if (!locked)
		UDAV_LOCK(sc);

	/* select internal PHY and set PHY register address */
	udav_csr_write1(sc, UDAV_EPAR,
	    UDAV_EPAR_PHY_ADR0 | (reg & UDAV_EPAR_EROA_MASK));

	/* select PHY operation and start read command */
	udav_csr_write1(sc, UDAV_EPCR, UDAV_EPCR_EPOS | UDAV_EPCR_ERPRR);

	/* XXX: should we wait? */

	/* end read command */
	UDAV_CLRBIT(sc, UDAV_EPCR, UDAV_EPCR_ERPRR);

	/* retrieve the result from data registers */
	udav_csr_read(sc, UDAV_EPDRL, val, 2);

	data16 = (val[0] | (val[1] << 8));

	DPRINTFN(11, "phy=%d reg=0x%04x => 0x%04x\n",
	    phy, reg, data16);

	if (!locked)
		UDAV_UNLOCK(sc);
	return (data16);
}