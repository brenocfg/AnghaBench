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
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_2__ {int mr_len; int mr_base; int /*<<< orphan*/  mr_flags; int /*<<< orphan*/  mr_owner; } ;
struct tdfx_softc {int addr0; int addr1; TYPE_1__ mrdesc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MDF_UNCACHEABLE ; 
 int /*<<< orphan*/  MDF_WRITECOMBINE ; 
 int MEMRANGE_SET_UPDATE ; 
 scalar_t__ PCI_DEVICE_3DFX_BANSHEE ; 
 scalar_t__ PCI_DEVICE_3DFX_VOODOO1 ; 
 scalar_t__ PCI_DEVICE_3DFX_VOODOO2 ; 
 scalar_t__ PCI_DEVICE_3DFX_VOODOO3 ; 
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ *,int) ; 
 struct tdfx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int mem_range_attr_set (TYPE_1__*,int*) ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tdfx_setmtrr(device_t dev) {
	/*
	 * This is the MTRR setting function for the 3dfx card. It is called from
	 * tdfx_attach. If we can't set the MTRR properly, it's not the end of the
	 * world. We can still continue, just with slightly (very slightly) degraded
	 * performance.
	 */
	int retval = 0, act;
	struct tdfx_softc *tdfx_info = device_get_softc(dev);

	/* The older Voodoo cards have a shorter memrange than the newer ones */
	if((pci_get_devid(dev) == PCI_DEVICE_3DFX_VOODOO1) || (pci_get_devid(dev) ==
			PCI_DEVICE_3DFX_VOODOO2)) {
		tdfx_info->mrdesc.mr_len = 0x400000;

		/* The memory descriptor is described as the top 15 bits of the real
			address */
		tdfx_info->mrdesc.mr_base = tdfx_info->addr0 & 0xfffe0000;
	}
	else if((pci_get_devid(dev) == PCI_DEVICE_3DFX_VOODOO3) ||
			(pci_get_devid(dev) == PCI_DEVICE_3DFX_BANSHEE)) {
		tdfx_info->mrdesc.mr_len = 0x1000000;
		/* The Voodoo3 and Banshee LFB is the second memory address */
		/* The memory descriptor is described as the top 15 bits of the real
			address */
		tdfx_info->mrdesc.mr_base = tdfx_info->addr1 & 0xfffe0000;
	}
	else
		 return 0;	
	/* 
    *	The Alliance Pro Motion AT3D was not mentioned in the linux
	 * driver as far as MTRR support goes, so I just won't put the
	 * code in here for it. This is where it should go, though. 
	 */

	/* Firstly, try to set write combining */
	tdfx_info->mrdesc.mr_flags = MDF_WRITECOMBINE;
	bcopy("tdfx", &tdfx_info->mrdesc.mr_owner, 4);
	act = MEMRANGE_SET_UPDATE;
	retval = mem_range_attr_set(&tdfx_info->mrdesc, &act);

	if(retval == 0) {
#ifdef DEBUG
		device_printf(dev, "MTRR Set Correctly for tdfx\n");
#endif
	} else if((pci_get_devid(dev) == PCI_DEVICE_3DFX_VOODOO2) ||
		(pci_get_devid(dev) == PCI_DEVICE_3DFX_VOODOO1)) {
		/* if, for some reason we can't set the WRCOMB range with the V1/V2, we
		 * can still possibly use the UNCACHEABLE region for it instead, and help
		 * out in a small way */
		tdfx_info->mrdesc.mr_flags = MDF_UNCACHEABLE;
		/* This length of 1000h was taken from the linux device driver... */
		tdfx_info->mrdesc.mr_len = 0x1000;

		/*
		 * If, for some reason, we can't set the MTRR (N/A?) we may still continue
		 */
#ifdef DEBUG
		device_printf(dev, "MTRR Set Type Uncacheable %x\n",
		    (u_int32_t)tdfx_info->mrdesc.mr_base);
#endif
	}
#ifdef DEBUG
	else {
		device_printf(dev, "Couldn't Set MTRR\n");
		return 0;
	}
#endif
	return 0;
}