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
struct ural_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int RAL_BBP_BUSY ; 
 int RAL_BBP_WRITE ; 
 int /*<<< orphan*/  RAL_PHY_CSR7 ; 
 int /*<<< orphan*/  RAL_PHY_CSR8 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 scalar_t__ ural_pause (struct ural_softc*,int) ; 
 int ural_read (struct ural_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ural_write (struct ural_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint8_t
ural_bbp_read(struct ural_softc *sc, uint8_t reg)
{
	uint16_t val;
	int ntries;

	val = RAL_BBP_WRITE | reg << 8;
	ural_write(sc, RAL_PHY_CSR7, val);

	for (ntries = 0; ntries < 100; ntries++) {
		if (!(ural_read(sc, RAL_PHY_CSR8) & RAL_BBP_BUSY))
			break;
		if (ural_pause(sc, hz / 100))
			break;
	}
	if (ntries == 100) {
		device_printf(sc->sc_dev, "could not read BBP\n");
		return 0;
	}

	return ural_read(sc, RAL_PHY_CSR7) & 0xff;
}