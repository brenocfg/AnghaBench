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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ const vm_offset_t ;
struct agp_i810_softc {int /*<<< orphan*/ * sc_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MEMATTR_WRITE_COMBINING ; 
 int /*<<< orphan*/  agp_i830_install_gatt_init (struct agp_i810_softc*) ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_change_attr (scalar_t__ const,scalar_t__ const,int /*<<< orphan*/ ) ; 
 scalar_t__ const rman_get_size (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_virtual (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agp_gen4_install_gatt(device_t dev, const vm_size_t gtt_offset)
{
	struct agp_i810_softc *sc;

	sc = device_get_softc(dev);
	pmap_change_attr((vm_offset_t)rman_get_virtual(sc->sc_res[0]) +
	    gtt_offset, rman_get_size(sc->sc_res[0]) - gtt_offset,
	    VM_MEMATTR_WRITE_COMBINING);
	agp_i830_install_gatt_init(sc);
	return (0);
}