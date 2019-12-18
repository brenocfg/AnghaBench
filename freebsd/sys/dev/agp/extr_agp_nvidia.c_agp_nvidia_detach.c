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
typedef  int u_int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  as_aperture; } ;
struct agp_nvidia_softc {int /*<<< orphan*/  gatt; int /*<<< orphan*/  initial_aperture; TYPE_1__ agp; int /*<<< orphan*/  mc2_dev; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_NVIDIA_0_APSIZE ; 
 int /*<<< orphan*/  AGP_NVIDIA_2_GARTCTRL ; 
 int /*<<< orphan*/  AGP_SET_APERTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_cdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_gatt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_res (int /*<<< orphan*/ ) ; 
 struct agp_nvidia_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvidia_init_iorr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agp_nvidia_detach (device_t dev)
{
	struct agp_nvidia_softc *sc = device_get_softc(dev);
	u_int32_t temp;

	agp_free_cdev(dev);

	/* GART Control */
	temp = pci_read_config(sc->dev, AGP_NVIDIA_0_APSIZE, 4);
	pci_write_config(sc->dev, AGP_NVIDIA_0_APSIZE, temp & ~(0x100), 4);

	/* GTLB Control */
	temp = pci_read_config(sc->mc2_dev, AGP_NVIDIA_2_GARTCTRL, 4);
	pci_write_config(sc->mc2_dev, AGP_NVIDIA_2_GARTCTRL, temp & ~(0x11), 4);

	/* Put the aperture back the way it started. */
	AGP_SET_APERTURE(dev, sc->initial_aperture);

	/* restore iorr for previous aperture size */
	nvidia_init_iorr(rman_get_start(sc->agp.as_aperture),
			 sc->initial_aperture);

	agp_free_gatt(sc->gatt);
	agp_free_res(dev);

	return (0);
}