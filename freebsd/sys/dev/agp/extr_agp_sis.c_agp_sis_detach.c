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
struct agp_sis_softc {int /*<<< orphan*/  gatt; int /*<<< orphan*/  initial_aperture; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_SET_APERTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AGP_SIS_TLBCTRL ; 
 int /*<<< orphan*/  AGP_SIS_WINCTRL ; 
 int /*<<< orphan*/  agp_free_cdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_gatt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_res (int /*<<< orphan*/ ) ; 
 struct agp_sis_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
agp_sis_detach(device_t dev)
{
	struct agp_sis_softc *sc = device_get_softc(dev);

	agp_free_cdev(dev);

	/* Disable the aperture.. */
	pci_write_config(dev, AGP_SIS_WINCTRL,
			 pci_read_config(dev, AGP_SIS_WINCTRL, 1) & ~3, 1);

	/* and the TLB. */
	pci_write_config(dev, AGP_SIS_TLBCTRL, 0, 1);

	/* Put the aperture back the way it started. */
	AGP_SET_APERTURE(dev, sc->initial_aperture);

	agp_free_gatt(sc->gatt);
	agp_free_res(dev);
	return 0;
}