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
struct intsmb_softc {int /*<<< orphan*/  io_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIIX4_SMBSLVSTS ; 
 int PIIX4_SMBSLVSTS_ALART ; 
 int PIIX4_SMBSLVSTS_BUSY ; 
 int PIIX4_SMBSLVSTS_SDW1 ; 
 int PIIX4_SMBSLVSTS_SDW2 ; 
 int PIIX4_SMBSLVSTS_SLV ; 
 int bus_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intsmb_alrintr (struct intsmb_softc*) ; 

__attribute__((used)) static int
intsmb_slvintr(struct intsmb_softc *sc)
{
	int status;

	status = bus_read_1(sc->io_res, PIIX4_SMBSLVSTS);
	if (status & PIIX4_SMBSLVSTS_BUSY)
		return (1);
	if (status & PIIX4_SMBSLVSTS_ALART)
		intsmb_alrintr(sc);
	else if (status & ~(PIIX4_SMBSLVSTS_ALART | PIIX4_SMBSLVSTS_SDW2
		| PIIX4_SMBSLVSTS_SDW1)) {
	}

	/* Reset Status Register */
	bus_write_1(sc->io_res, PIIX4_SMBSLVSTS,
	    PIIX4_SMBSLVSTS_ALART | PIIX4_SMBSLVSTS_SDW2 |
	    PIIX4_SMBSLVSTS_SDW1 | PIIX4_SMBSLVSTS_SLV);
	return (0);
}