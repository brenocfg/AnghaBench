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
typedef  int u_int ;
struct sbus_softc {int /*<<< orphan*/  sc_ign; int /*<<< orphan*/  sc_dev; } ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int INTMAP_OBIO_MASK ; 
 scalar_t__ INTMAP_VEC (int /*<<< orphan*/ ,int) ; 
 int INTPRI (int) ; 
 int INTSLOT (int) ; 
 scalar_t__ INTVEC (int /*<<< orphan*/ ) ; 
 scalar_t__ SBR_RESERVED_INT_MAP ; 
 scalar_t__ SBR_SCSI_INT_CLR ; 
 scalar_t__ SBR_SCSI_INT_MAP ; 
 scalar_t__ SBR_SLOT0_INT_CLR ; 
 scalar_t__ SBR_SLOT0_INT_MAP ; 
 int SBUS_MAX_INO ; 
 int /*<<< orphan*/  SYSIO_READ8 (struct sbus_softc*,scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
sbus_find_intrmap(struct sbus_softc *sc, u_int ino, bus_addr_t *intrmapptr,
    bus_addr_t *intrclrptr)
{
	bus_addr_t intrclr, intrmap;
	int i;

	if (ino > SBUS_MAX_INO) {
		device_printf(sc->sc_dev, "out of range INO %d requested\n",
		    ino);
		return (0);
	}

	if ((ino & INTMAP_OBIO_MASK) == 0) {
		intrmap = SBR_SLOT0_INT_MAP + INTSLOT(ino) * 8;
		intrclr = SBR_SLOT0_INT_CLR +
		    (INTSLOT(ino) * 8 * 8) + (INTPRI(ino) * 8);
	} else {
		intrclr = 0;
		for (i = 0, intrmap = SBR_SCSI_INT_MAP;
		    intrmap <= SBR_RESERVED_INT_MAP; intrmap += 8, i++) {
			if (INTVEC(SYSIO_READ8(sc, intrmap)) ==
			    INTMAP_VEC(sc->sc_ign, ino)) {
				intrclr = SBR_SCSI_INT_CLR + i * 8;
				break;
			}
		}
		if (intrclr == 0)
			return (0);
	}
	if (intrmapptr != NULL)
		*intrmapptr = intrmap;
	if (intrclrptr != NULL)
		*intrclrptr = intrclr;
	return (1);
}