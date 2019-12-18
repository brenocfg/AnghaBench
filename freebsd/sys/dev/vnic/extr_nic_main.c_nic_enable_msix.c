#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int msix_table_bar; } ;
struct TYPE_4__ {TYPE_1__ msix; } ;
struct pci_devinfo {TYPE_2__ cfg; } ;
struct nicpf {int num_vec; int msix_enabled; int /*<<< orphan*/  dev; int /*<<< orphan*/ * msix_table_res; } ;

/* Variables and functions */
 int ENXIO ; 
 int NIC_PF_MSIX_VECTORS ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int pci_alloc_msix (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
nic_enable_msix(struct nicpf *nic)
{
	struct pci_devinfo *dinfo;
	int rid, count;
	int ret;

	dinfo = device_get_ivars(nic->dev);
	rid = dinfo->cfg.msix.msix_table_bar;
	nic->msix_table_res =
	    bus_alloc_resource_any(nic->dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (nic->msix_table_res == NULL) {
		device_printf(nic->dev,
		    "Could not allocate memory for MSI-X table\n");
		return (ENXIO);
	}

	count = nic->num_vec = NIC_PF_MSIX_VECTORS;

	ret = pci_alloc_msix(nic->dev, &count);
	if ((ret != 0) || (count != nic->num_vec)) {
		device_printf(nic->dev,
		    "Request for #%d msix vectors failed, error: %d\n",
		    nic->num_vec, ret);
		return (ret);
	}

	nic->msix_enabled = 1;
	return (0);
}