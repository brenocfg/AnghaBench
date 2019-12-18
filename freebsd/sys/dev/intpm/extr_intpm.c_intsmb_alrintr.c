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
typedef  void* uint8_t ;
struct intsmb_softc {int /*<<< orphan*/  io_res; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int LSB ; 
 int /*<<< orphan*/  PIIX4_SMBHSTADD ; 
 int /*<<< orphan*/  PIIX4_SMBHSTCNT_PROT_BYTE ; 
 int /*<<< orphan*/  PIIX4_SMBHSTDAT0 ; 
 int /*<<< orphan*/  PIIX4_SMBSLVCNT ; 
 int PIIX4_SMBSLVCNT_ALTEN ; 
 int SMBALTRESP ; 
 void* bus_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int intsmb_free (struct intsmb_softc*) ; 
 int /*<<< orphan*/  intsmb_start (struct intsmb_softc*,int /*<<< orphan*/ ,int) ; 
 int intsmb_stop_poll (struct intsmb_softc*) ; 

__attribute__((used)) static void
intsmb_alrintr(struct intsmb_softc *sc)
{
	int slvcnt;
#ifdef ENABLE_ALART
	int error;
	uint8_t addr;
#endif

	/* Stop generating INTR from ALART. */
	slvcnt = bus_read_1(sc->io_res, PIIX4_SMBSLVCNT);
#ifdef ENABLE_ALART
	bus_write_1(sc->io_res, PIIX4_SMBSLVCNT,
	    slvcnt & ~PIIX4_SMBSLVCNT_ALTEN);
#endif
	DELAY(5);

	/* Ask bus who asserted it and then ask it what's the matter. */
#ifdef ENABLE_ALART
	error = intsmb_free(sc);
	if (error)
		return;

	bus_write_1(sc->io_res, PIIX4_SMBHSTADD, SMBALTRESP | LSB);
	intsmb_start(sc, PIIX4_SMBHSTCNT_PROT_BYTE, 1);
	error = intsmb_stop_poll(sc);
	if (error)
		device_printf(sc->dev, "ALART: ERROR\n");
	else {
		addr = bus_read_1(sc->io_res, PIIX4_SMBHSTDAT0);
		device_printf(sc->dev, "ALART_RESPONSE: 0x%x\n", addr);
	}

	/* Re-enable INTR from ALART. */
	bus_write_1(sc->io_res, PIIX4_SMBSLVCNT,
	    slvcnt | PIIX4_SMBSLVCNT_ALTEN);
	DELAY(5);
#endif
}