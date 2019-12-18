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
struct nvme_controller {scalar_t__ msix_enabled; int /*<<< orphan*/ * res; scalar_t__ tag; int /*<<< orphan*/ * bar4_resource; int /*<<< orphan*/  bar4_resource_id; int /*<<< orphan*/ * resource; int /*<<< orphan*/  resource_id; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct nvme_controller* DEVICE2SOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int nvme_attach (int /*<<< orphan*/ ) ; 
 int nvme_ctrlr_allocate_bar (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_ctrlr_setup_interrupts (struct nvme_controller*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nvme_pci_attach(device_t dev)
{
	struct nvme_controller*ctrlr = DEVICE2SOFTC(dev);
	int status;

	ctrlr->dev = dev;
	status = nvme_ctrlr_allocate_bar(ctrlr);
	if (status != 0)
		goto bad;
	pci_enable_busmaster(dev);
	nvme_ctrlr_setup_interrupts(ctrlr);
	return nvme_attach(dev);
bad:
	if (ctrlr->resource != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY,
		    ctrlr->resource_id, ctrlr->resource);
	}

	if (ctrlr->bar4_resource != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY,
		    ctrlr->bar4_resource_id, ctrlr->bar4_resource);
	}

	if (ctrlr->tag)
		bus_teardown_intr(dev, ctrlr->res, ctrlr->tag);

	if (ctrlr->res)
		bus_release_resource(dev, SYS_RES_IRQ,
		    rman_get_rid(ctrlr->res), ctrlr->res);

	if (ctrlr->msix_enabled)
		pci_release_msi(dev);

	return status;
}