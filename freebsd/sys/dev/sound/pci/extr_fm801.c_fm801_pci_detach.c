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
struct fm801_info {int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/  irq; int /*<<< orphan*/  irqid; int /*<<< orphan*/  ih; int /*<<< orphan*/  reg; int /*<<< orphan*/  regid; int /*<<< orphan*/  regtype; int /*<<< orphan*/ * radio; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct fm801_info*,int /*<<< orphan*/ ) ; 
 struct fm801_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fm801_pci_detach(device_t dev)
{
	int r;
	struct fm801_info *fm801;

	DPRINT("Forte Media FM801 detach\n");

	fm801 = pcm_getdevinfo(dev);

	r = bus_generic_detach(dev);
	if (r)
		return r;
	if (fm801->radio != NULL) {
		r = device_delete_child(dev, fm801->radio);
		if (r)
			return r;
		fm801->radio = NULL;
	}

	r = pcm_unregister(dev);
	if (r)
		return r;

	bus_release_resource(dev, fm801->regtype, fm801->regid, fm801->reg);
	bus_teardown_intr(dev, fm801->irq, fm801->ih);
	bus_release_resource(dev, SYS_RES_IRQ, fm801->irqid, fm801->irq);
	bus_dma_tag_destroy(fm801->parent_dmat);
	free(fm801, M_DEVBUF);
	return 0;
}