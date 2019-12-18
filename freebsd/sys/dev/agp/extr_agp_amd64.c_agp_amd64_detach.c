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
struct agp_amd64_softc {int n_mctrl; int /*<<< orphan*/  gatt; int /*<<< orphan*/  initial_aperture; int /*<<< orphan*/ * mctrl; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_AMD64_APCTRL ; 
 int AGP_AMD64_APCTRL_GARTEN ; 
 int /*<<< orphan*/  AGP_SET_APERTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_cdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_gatt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_res (int /*<<< orphan*/ ) ; 
 struct agp_amd64_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_cfgregread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_cfgregwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
agp_amd64_detach(device_t dev)
{
	struct agp_amd64_softc *sc = device_get_softc(dev);
	int i;

	agp_free_cdev(dev);

	for (i = 0; i < sc->n_mctrl; i++)
		pci_cfgregwrite(0, sc->mctrl[i], 3, AGP_AMD64_APCTRL,
		    pci_cfgregread(0, sc->mctrl[i], 3, AGP_AMD64_APCTRL, 4) &
		    ~AGP_AMD64_APCTRL_GARTEN, 4);

	AGP_SET_APERTURE(dev, sc->initial_aperture);
	agp_free_gatt(sc->gatt);
	agp_free_res(dev);

	return (0);
}