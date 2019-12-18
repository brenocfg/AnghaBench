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
typedef  int /*<<< orphan*/  val16 ;
typedef  int u8 ;
typedef  int u16 ;
struct bcma_drv_pci {TYPE_1__* core; } ;
struct bcma_bus {int dummy; } ;
struct TYPE_2__ {struct bcma_bus* bus; } ;

/* Variables and functions */
 int BCMA_CORE_PCI_RC_CRS_VISIBILITY ; 
 int BCMA_PCI_SLOT_MAX ; 
 int /*<<< orphan*/  PCI_CAP_ID_EXP ; 
 int PCI_EXP_RTCAP ; 
 int PCI_EXP_RTCTL ; 
 int PCI_EXP_RTCTL_CRSSVE ; 
 int PCI_VENDOR_ID ; 
 int /*<<< orphan*/  bcma_err (struct bcma_bus*,char*,int) ; 
 int /*<<< orphan*/  bcma_extpci_read_config (struct bcma_drv_pci*,int,int /*<<< orphan*/ ,int,int*,int) ; 
 int bcma_find_pci_capability (struct bcma_drv_pci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void bcma_core_pci_enable_crs(struct bcma_drv_pci *pc)
{
	struct bcma_bus *bus = pc->core->bus;
	u8 cap_ptr, root_ctrl, root_cap, dev;
	u16 val16;
	int i;

	cap_ptr = bcma_find_pci_capability(pc, 0, 0, PCI_CAP_ID_EXP, NULL,
					   NULL);
	root_cap = cap_ptr + PCI_EXP_RTCAP;
	bcma_extpci_read_config(pc, 0, 0, root_cap, &val16, sizeof(u16));
	if (val16 & BCMA_CORE_PCI_RC_CRS_VISIBILITY) {
		/* Enable CRS software visibility */
		root_ctrl = cap_ptr + PCI_EXP_RTCTL;
		val16 = PCI_EXP_RTCTL_CRSSVE;
		bcma_extpci_read_config(pc, 0, 0, root_ctrl, &val16,
					sizeof(u16));

		/* Initiate a configuration request to read the vendor id
		 * field of the device function's config space header after
		 * 100 ms wait time from the end of Reset. If the device is
		 * not done with its internal initialization, it must at
		 * least return a completion TLP, with a completion status
		 * of "Configuration Request Retry Status (CRS)". The root
		 * complex must complete the request to the host by returning
		 * a read-data value of 0001h for the Vendor ID field and
		 * all 1s for any additional bytes included in the request.
		 * Poll using the config reads for max wait time of 1 sec or
		 * until we receive the successful completion status. Repeat
		 * the procedure for all the devices.
		 */
		for (dev = 1; dev < BCMA_PCI_SLOT_MAX; dev++) {
			for (i = 0; i < 100000; i++) {
				bcma_extpci_read_config(pc, dev, 0,
							PCI_VENDOR_ID, &val16,
							sizeof(val16));
				if (val16 != 0x1)
					break;
				udelay(10);
			}
			if (val16 == 0x1)
				bcma_err(bus, "PCI: Broken device in slot %d\n",
					 dev);
		}
	}
}