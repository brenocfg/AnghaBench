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
typedef  int u_int32_t ;
struct agp_ali_softc {int /*<<< orphan*/  gatt; int /*<<< orphan*/  initial_aperture; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_ALI_ATTBASE ; 
 int /*<<< orphan*/  AGP_ALI_TLBCTRL ; 
 int /*<<< orphan*/  AGP_SET_APERTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_cdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_gatt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_res (int /*<<< orphan*/ ) ; 
 struct agp_ali_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
agp_ali_detach(device_t dev)
{
	struct agp_ali_softc *sc = device_get_softc(dev);
	u_int32_t attbase;

	agp_free_cdev(dev);

	/* Disable the TLB.. */
	pci_write_config(dev, AGP_ALI_TLBCTRL, 0x90, 1);

	/* Put the aperture back the way it started. */
	AGP_SET_APERTURE(dev, sc->initial_aperture);
	attbase = pci_read_config(dev, AGP_ALI_ATTBASE, 4);
	pci_write_config(dev, AGP_ALI_ATTBASE, attbase & 0xfff, 4);

	agp_free_gatt(sc->gatt);
	agp_free_res(dev);
	return 0;
}