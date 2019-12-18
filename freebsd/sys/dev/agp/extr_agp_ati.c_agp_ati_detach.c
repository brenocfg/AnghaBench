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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int u_int32_t ;
struct agp_ati_softc {int ag_entries; int /*<<< orphan*/  regs; scalar_t__ ag_virtual; scalar_t__ ag_vdir; int /*<<< orphan*/  initial_aperture; scalar_t__ is_rs300; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AGP_PAGE_SIZE ; 
 int /*<<< orphan*/  AGP_SET_APERTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATI_GART_BASE ; 
 int /*<<< orphan*/  ATI_GART_MMADDR ; 
 int ATI_RS100_APSIZE ; 
 int ATI_RS300_APSIZE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  WRITE4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_cdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_res (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct agp_ati_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
agp_ati_detach(device_t dev)
{
	struct agp_ati_softc *sc = device_get_softc(dev);
	u_int32_t apsize_reg, temp;

	agp_free_cdev(dev);

	if (sc->is_rs300)
		apsize_reg = ATI_RS300_APSIZE;
	else
		apsize_reg = ATI_RS100_APSIZE;

	/* Clear the GATT base */
	WRITE4(ATI_GART_BASE, 0);

	/* Put the aperture back the way it started. */
	AGP_SET_APERTURE(dev, sc->initial_aperture);

	temp = pci_read_config(dev, apsize_reg, 4);
	pci_write_config(dev, apsize_reg, temp & ~1, 4);

	kmem_free((vm_offset_t)sc->ag_vdir, AGP_PAGE_SIZE);
	kmem_free((vm_offset_t)sc->ag_virtual, sc->ag_entries *
	    sizeof(u_int32_t));

	bus_release_resource(dev, SYS_RES_MEMORY, ATI_GART_MMADDR, sc->regs);
	agp_free_res(dev);

	return 0;
}