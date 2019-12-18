#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int /*<<< orphan*/  mem_bus_space_handle; int /*<<< orphan*/  dev; int /*<<< orphan*/  flush_reg; int /*<<< orphan*/  mem_bus_space_size; int /*<<< orphan*/  mem_bus_space_tag; } ;
struct TYPE_5__ {int /*<<< orphan*/  func; int /*<<< orphan*/  device; } ;
struct i40e_hw {TYPE_3__* back; int /*<<< orphan*/ * hw_addr; TYPE_2__ bus; void* subsystem_device_id; void* subsystem_vendor_id; void* revision_id; int /*<<< orphan*/  device_id; int /*<<< orphan*/  vendor_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctx; } ;
struct iavf_sc {TYPE_3__ osdep; struct i40e_hw hw; int /*<<< orphan*/  pci_mem; TYPE_1__ vsi; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  I40E_VFGEN_RSTAT ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIR_REVID ; 
 int /*<<< orphan*/  PCIR_SUBDEV_0 ; 
 int /*<<< orphan*/  PCIR_SUBVEND_0 ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_vendor (int /*<<< orphan*/ ) ; 
 void* pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iavf_allocate_pci_resources(struct iavf_sc *sc)
{
	struct i40e_hw *hw = &sc->hw;
	device_t dev = iflib_get_dev(sc->vsi.ctx);
	int             rid;

	/* Map BAR0 */
	rid = PCIR_BAR(0);
	sc->pci_mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &rid, RF_ACTIVE);

	if (!(sc->pci_mem)) {
		device_printf(dev, "Unable to allocate bus resource: PCI memory\n");
		return (ENXIO);
 	}
 
	/* Save off the PCI information */
	hw->vendor_id = pci_get_vendor(dev);
	hw->device_id = pci_get_device(dev);
	hw->revision_id = pci_read_config(dev, PCIR_REVID, 1);
	hw->subsystem_vendor_id =
	    pci_read_config(dev, PCIR_SUBVEND_0, 2);
	hw->subsystem_device_id =
	    pci_read_config(dev, PCIR_SUBDEV_0, 2);

	hw->bus.device = pci_get_slot(dev);
	hw->bus.func = pci_get_function(dev);

	/* Save off register access information */
	sc->osdep.mem_bus_space_tag =
		rman_get_bustag(sc->pci_mem);
	sc->osdep.mem_bus_space_handle =
		rman_get_bushandle(sc->pci_mem);
	sc->osdep.mem_bus_space_size = rman_get_size(sc->pci_mem);
	sc->osdep.flush_reg = I40E_VFGEN_RSTAT;
	sc->osdep.dev = dev;

	sc->hw.hw_addr = (u8 *) &sc->osdep.mem_bus_space_handle;
	sc->hw.back = &sc->osdep;

 	return (0);
}