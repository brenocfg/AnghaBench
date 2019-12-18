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
struct nvme_registers {int dummy; } ;
struct nvme_controller {int num_io_queues; int /*<<< orphan*/ * res; int /*<<< orphan*/  dev; int /*<<< orphan*/ * resource; scalar_t__ resource_id; void* tag; scalar_t__ msix_enabled; scalar_t__ rid; scalar_t__ bus_handle; struct nvme_registers* regs; int /*<<< orphan*/  bus_tag; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct nvme_controller* DEVICE2SOFTC (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nvme_controller*,void**) ; 
 int nvme_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_ctrlr_intx_handler ; 
 int /*<<< orphan*/  nvme_printf (struct nvme_controller*,char*) ; 
 scalar_t__ rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 scalar_t__ rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nvme_ahci_attach(device_t dev)
{
	struct nvme_controller*ctrlr = DEVICE2SOFTC(dev);
	int ret;

	/* Map MMIO registers */
	ctrlr->resource_id = 0;

	ctrlr->resource = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &ctrlr->resource_id, RF_ACTIVE);

	if(ctrlr->resource == NULL) {
		nvme_printf(ctrlr, "unable to allocate mem resource\n");
		ret = ENOMEM;
		goto bad;
	}
	ctrlr->bus_tag = rman_get_bustag(ctrlr->resource);
	ctrlr->bus_handle = rman_get_bushandle(ctrlr->resource);
	ctrlr->regs = (struct nvme_registers *)ctrlr->bus_handle;

	/* Allocate and setup IRQ */
	ctrlr->rid = 0;
	ctrlr->res = bus_alloc_resource_any(dev, SYS_RES_IRQ,
	    &ctrlr->rid, RF_SHAREABLE | RF_ACTIVE);

	if (ctrlr->res == NULL) {
		nvme_printf(ctrlr, "unable to allocate shared IRQ\n");
		ret = ENOMEM;
		goto bad;
	}

	ctrlr->msix_enabled = 0;
	ctrlr->num_io_queues = 1;
	if (bus_setup_intr(dev, ctrlr->res,
	    INTR_TYPE_MISC | INTR_MPSAFE, NULL, nvme_ctrlr_intx_handler,
	    ctrlr, &ctrlr->tag) != 0) {
		nvme_printf(ctrlr, "unable to setup intx handler\n");
		ret = ENOMEM;
		goto bad;
	}
	ctrlr->tag = (void *)0x1;

	return nvme_attach(dev);
bad:
	if (ctrlr->resource != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY,
		    ctrlr->resource_id, ctrlr->resource);
	}
	if (ctrlr->res)
		bus_release_resource(ctrlr->dev, SYS_RES_IRQ,
		    rman_get_rid(ctrlr->res), ctrlr->res);
	return (ret);
}