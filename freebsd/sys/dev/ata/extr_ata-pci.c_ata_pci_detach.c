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
struct ata_pci_controller {scalar_t__ r_irq_rid; scalar_t__ r_rid2; scalar_t__ r_rid1; scalar_t__ r_res1; int /*<<< orphan*/  r_type1; scalar_t__ r_res2; int /*<<< orphan*/  r_type2; int /*<<< orphan*/  (* chipdeinit ) (int /*<<< orphan*/ ) ;scalar_t__ r_irq; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ ATA_IRQ_RID ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (scalar_t__) ; 
 int /*<<< orphan*/  rman_get_bustag (scalar_t__) ; 
 int /*<<< orphan*/  rman_get_size (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

int
ata_pci_detach(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(dev);

    /* detach & delete all children */
    device_delete_children(dev);

    if (ctlr->r_irq) {
	bus_teardown_intr(dev, ctlr->r_irq, ctlr->handle);
	bus_release_resource(dev, SYS_RES_IRQ, ctlr->r_irq_rid, ctlr->r_irq);
	if (ctlr->r_irq_rid != ATA_IRQ_RID)
	    pci_release_msi(dev);
    }
    if (ctlr->chipdeinit != NULL)
	ctlr->chipdeinit(dev);
    if (ctlr->r_res2) {
#ifdef __sparc64__
	bus_space_unmap(rman_get_bustag(ctlr->r_res2),
	    rman_get_bushandle(ctlr->r_res2), rman_get_size(ctlr->r_res2));
#endif
	bus_release_resource(dev, ctlr->r_type2, ctlr->r_rid2, ctlr->r_res2);
    }
    if (ctlr->r_res1) {
#ifdef __sparc64__
	bus_space_unmap(rman_get_bustag(ctlr->r_res1),
	    rman_get_bushandle(ctlr->r_res1), rman_get_size(ctlr->r_res1));
#endif
	bus_release_resource(dev, ctlr->r_type1, ctlr->r_rid1, ctlr->r_res1);
    }

    return 0;
}