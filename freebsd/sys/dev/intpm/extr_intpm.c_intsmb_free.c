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
struct intsmb_softc {int isbusy; int /*<<< orphan*/  io_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTSMB_LOCK_ASSERT (struct intsmb_softc*) ; 
 int PIIX4_SMBHSTSTAT_BUSC ; 
 int PIIX4_SMBHSTSTAT_BUSY ; 
 int PIIX4_SMBHSTSTAT_ERR ; 
 int PIIX4_SMBHSTSTAT_FAIL ; 
 int PIIX4_SMBHSTSTAT_INTR ; 
 int /*<<< orphan*/  PIIX4_SMBHSTSTS ; 
 int /*<<< orphan*/  PIIX4_SMBSLVCNT ; 
 int /*<<< orphan*/  PIIX4_SMBSLVSTS ; 
 int PIIX4_SMBSLVSTS_BUSY ; 
 int SMB_EBUSY ; 
 int bus_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
intsmb_free(struct intsmb_softc *sc)
{

	INTSMB_LOCK_ASSERT(sc);
	if ((bus_read_1(sc->io_res, PIIX4_SMBHSTSTS) & PIIX4_SMBHSTSTAT_BUSY) ||
#ifdef ENABLE_ALART
	    (bus_read_1(sc->io_res, PIIX4_SMBSLVSTS) & PIIX4_SMBSLVSTS_BUSY) ||
#endif
	    sc->isbusy)
		return (SMB_EBUSY);

	sc->isbusy = 1;
	/* Disable Interrupt in slave part. */
#ifndef ENABLE_ALART
	bus_write_1(sc->io_res, PIIX4_SMBSLVCNT, 0);
#endif
	/* Reset INTR Flag to prepare INTR. */
	bus_write_1(sc->io_res, PIIX4_SMBHSTSTS,
	    PIIX4_SMBHSTSTAT_INTR | PIIX4_SMBHSTSTAT_ERR |
	    PIIX4_SMBHSTSTAT_BUSC | PIIX4_SMBHSTSTAT_FAIL);
	return (0);
}