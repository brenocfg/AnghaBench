#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
struct agp_i810_softc {TYPE_1__* gatt; int /*<<< orphan*/ * sc_res; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ ag_virtual; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_I810_PGTBL_CTL ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
agp_i810_deinstall_gatt(device_t dev)
{
	struct agp_i810_softc *sc;

	sc = device_get_softc(dev);
	bus_write_4(sc->sc_res[0], AGP_I810_PGTBL_CTL, 0);
	kmem_free((vm_offset_t)sc->gatt->ag_virtual, 64 * 1024);
}