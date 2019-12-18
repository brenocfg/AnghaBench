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
struct TYPE_2__ {int /*<<< orphan*/ * mem; int /*<<< orphan*/  mem_rid; int /*<<< orphan*/ * io; int /*<<< orphan*/  io_rid; int /*<<< orphan*/ * irq; int /*<<< orphan*/  irq_rid; } ;
struct csa_info {int /*<<< orphan*/ * parent_dmat; int /*<<< orphan*/  ih; TYPE_1__ res; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  TYPE_1__ csa_res ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct csa_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
csa_releaseres(struct csa_info *csa, device_t dev)
{
	csa_res *resp;

	KASSERT(csa != NULL, ("called with bogus resource structure"));

	resp = &csa->res;
	if (resp->irq != NULL) {
		if (csa->ih)
			bus_teardown_intr(dev, resp->irq, csa->ih);
		bus_release_resource(dev, SYS_RES_IRQ, resp->irq_rid, resp->irq);
		resp->irq = NULL;
	}
	if (resp->io != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY, resp->io_rid, resp->io);
		resp->io = NULL;
	}
	if (resp->mem != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY, resp->mem_rid, resp->mem);
		resp->mem = NULL;
	}
	if (csa->parent_dmat != NULL) {
		bus_dma_tag_destroy(csa->parent_dmat);
		csa->parent_dmat = NULL;
	}

	free(csa, M_DEVBUF);
}