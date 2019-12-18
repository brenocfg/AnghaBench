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
struct tdfx_softc {int /*<<< orphan*/  devt; int /*<<< orphan*/  memrange; int /*<<< orphan*/  memrid2; int /*<<< orphan*/ * memrange2; int /*<<< orphan*/  memrid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_3DFX_BANSHEE ; 
 scalar_t__ PCI_DEVICE_3DFX_VOODOO3 ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 struct tdfx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int tdfx_clrmtrr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tdfx_detach(device_t dev) {
	struct tdfx_softc* tdfx_info;
	int retval;
	tdfx_info = device_get_softc(dev);
	
	/* Delete allocated resource, of course */
	bus_release_resource(dev, SYS_RES_MEMORY, tdfx_info->memrid,
			tdfx_info->memrange);

	/* Release extended Voodoo3/Banshee resources */
	if(pci_get_devid(dev) == PCI_DEVICE_3DFX_BANSHEE || 
			pci_get_devid(dev) == PCI_DEVICE_3DFX_VOODOO3) {
		if(tdfx_info->memrange2 != NULL)
			bus_release_resource(dev, SYS_RES_MEMORY, tdfx_info->memrid2,
				tdfx_info->memrange);
	/*	if(tdfx_info->piorange != NULL)
			bus_release_resource(dev, SYS_RES_IOPORT, tdfx_info->piorid,
				tdfx_info->piorange);*/
	}		

	/* Though it is safe to leave the WRCOMB support since the 
		mem driver checks for it, we should remove it in order
		to free an MTRR for another device */
	retval = tdfx_clrmtrr(dev);
#ifdef DEBUG
	if(retval != 0) 
		printf("tdfx: For some reason, I couldn't clear the mtrr\n");
#endif
	/* Remove device entry when it can no longer be accessed */
   destroy_dev(tdfx_info->devt);
	return(0);
}