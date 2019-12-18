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
struct fire_softc {int /*<<< orphan*/  sc_dev; } ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int FO_MAX_INO ; 
 scalar_t__ FO_PCI_INT_CLR_BASE ; 
 scalar_t__ FO_PCI_INT_MAP_BASE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
fire_get_intrmap(struct fire_softc *sc, u_int ino, bus_addr_t *intrmapptr,
    bus_addr_t *intrclrptr)
{

	if (ino > FO_MAX_INO) {
		device_printf(sc->sc_dev, "out of range INO %d requested\n",
		    ino);
		return (0);
	}

	ino <<= 3;
	if (intrmapptr != NULL)
		*intrmapptr = FO_PCI_INT_MAP_BASE + ino;
	if (intrclrptr != NULL)
		*intrclrptr = FO_PCI_INT_CLR_BASE + ino;
	return (1);
}