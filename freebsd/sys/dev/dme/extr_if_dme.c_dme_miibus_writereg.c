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
 int EPCR_ERPRW ; 
 int EPCR_ERRE ; 
 struct dme_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int dme_read_reg (struct dme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dme_write_reg (struct dme_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dme_miibus_writereg(device_t dev, int phy, int reg, int data)
{
	struct dme_softc *sc;
	int i;

	/* We have up to 4 PHY's */
	if (phy > 3)
		return (0);

	sc = device_get_softc(dev);

	/* Send the register and data to write to the phy */
	dme_write_reg(sc, DME_EPAR, (phy << 6) | reg);
	dme_write_reg(sc, DME_EPDRL, data & 0xFF);
	dme_write_reg(sc, DME_EPDRH, (data >> 8) & 0xFF);
	/* Start the write */
	dme_write_reg(sc, DME_EPCR, EPCR_EPOS | EPCR_ERPRW);

	/* Wait for the data to be written */
	for (i = 0; i < DME_TIMEOUT; i++) {
		if ((dme_read_reg(sc, DME_EPCR) & EPCR_ERRE) == 0)
			break;
		DELAY(1);
	}

	/* Clear the comand */
	dme_write_reg(sc, DME_EPCR, 0);

	return (0);
}