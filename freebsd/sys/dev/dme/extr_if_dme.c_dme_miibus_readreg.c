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
struct dme_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DME_EPAR ; 
 int /*<<< orphan*/  DME_EPCR ; 
 int /*<<< orphan*/  DME_EPDRH ; 
 int /*<<< orphan*/  DME_EPDRL ; 
 int DME_TIMEOUT ; 
 int EPCR_EPOS ; 
 int EPCR_ERPRR ; 
 int EPCR_ERRE ; 
 struct dme_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int dme_read_reg (struct dme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dme_write_reg (struct dme_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dme_miibus_readreg(device_t dev, int phy, int reg)
{
	struct dme_softc *sc;
	int i, rval;

	/* We have up to 4 PHY's */
	if (phy >= 4)
		return (0);

	sc = device_get_softc(dev);

	/* Send the register to read to the phy and start the read */
	dme_write_reg(sc, DME_EPAR, (phy << 6) | reg);
	dme_write_reg(sc, DME_EPCR, EPCR_EPOS | EPCR_ERPRR);

	/* Wait for the data to be read */
	for (i = 0; i < DME_TIMEOUT; i++) {
		if ((dme_read_reg(sc, DME_EPCR) & EPCR_ERRE) == 0)
			break;
		DELAY(1);
	}

	/* Clear the comand */
	dme_write_reg(sc, DME_EPCR, 0);

	if (i == DME_TIMEOUT)
		return (0);

	rval = (dme_read_reg(sc, DME_EPDRH) << 8) | dme_read_reg(sc, DME_EPDRL);
	return (rval);
}