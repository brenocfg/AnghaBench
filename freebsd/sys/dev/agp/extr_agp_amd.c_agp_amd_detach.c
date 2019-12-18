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
struct agp_amd_softc {int /*<<< orphan*/  regs; int /*<<< orphan*/  gatt; int /*<<< orphan*/  initial_aperture; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_AMD751_ATTBASE ; 
 int /*<<< orphan*/  AGP_AMD751_MODECTRL ; 
 int /*<<< orphan*/  AGP_AMD751_REGISTERS ; 
 int /*<<< orphan*/  AGP_AMD751_STATUS ; 
 int AGP_AMD751_STATUS_GCE ; 
 int /*<<< orphan*/  AGP_SET_APERTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int READ2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  WRITE2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_amd_free_gatt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_cdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_res (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct agp_amd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
agp_amd_detach(device_t dev)
{
	struct agp_amd_softc *sc = device_get_softc(dev);

	agp_free_cdev(dev);

	/* Disable the TLB.. */
	WRITE2(AGP_AMD751_STATUS,
	       READ2(AGP_AMD751_STATUS) & ~AGP_AMD751_STATUS_GCE);
	
	/* Disable host-agp sync */
	pci_write_config(dev, AGP_AMD751_MODECTRL, 0x00, 1);
	
	/* Clear the GATT base */
	WRITE4(AGP_AMD751_ATTBASE, 0);

	/* Put the aperture back the way it started. */
	AGP_SET_APERTURE(dev, sc->initial_aperture);

	agp_amd_free_gatt(sc->gatt);
	agp_free_res(dev);

	bus_release_resource(dev, SYS_RES_MEMORY,
			     AGP_AMD751_REGISTERS, sc->regs);

	return 0;
}