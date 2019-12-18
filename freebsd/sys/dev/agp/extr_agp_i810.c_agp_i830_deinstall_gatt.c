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
struct agp_i810_softc {int /*<<< orphan*/ * sc_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_I810_PGTBL_CTL ; 
 unsigned int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
agp_i830_deinstall_gatt(device_t dev)
{
	struct agp_i810_softc *sc;
	unsigned int pgtblctl;

	sc = device_get_softc(dev);
	pgtblctl = bus_read_4(sc->sc_res[0], AGP_I810_PGTBL_CTL);
	pgtblctl &= ~1;
	bus_write_4(sc->sc_res[0], AGP_I810_PGTBL_CTL, pgtblctl);
}