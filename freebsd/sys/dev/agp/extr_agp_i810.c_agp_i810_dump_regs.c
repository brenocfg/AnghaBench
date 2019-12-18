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
struct agp_i810_softc {int /*<<< orphan*/  bdev; int /*<<< orphan*/ * sc_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_I810_MISCC ; 
 int /*<<< orphan*/  AGP_I810_PGTBL_CTL ; 
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
agp_i810_dump_regs(device_t dev)
{
	struct agp_i810_softc *sc = device_get_softc(dev);

	device_printf(dev, "AGP_I810_PGTBL_CTL: %08x\n",
	    bus_read_4(sc->sc_res[0], AGP_I810_PGTBL_CTL));
	device_printf(dev, "AGP_I810_MISCC: 0x%04x\n",
	    pci_read_config(sc->bdev, AGP_I810_MISCC, 2));
}