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
struct ad1816_info {scalar_t__ lock; scalar_t__ parent_dmat; int /*<<< orphan*/ * io_base; int /*<<< orphan*/  io_rid; int /*<<< orphan*/ * drq2; int /*<<< orphan*/  drq2_rid; int /*<<< orphan*/ * drq1; int /*<<< orphan*/  drq1_rid; int /*<<< orphan*/ * irq; int /*<<< orphan*/  irq_rid; scalar_t__ ih; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  free (struct ad1816_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_dma_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mtxfree (scalar_t__) ; 

__attribute__((used)) static void
ad1816_release_resources(struct ad1816_info *ad1816, device_t dev)
{
    	if (ad1816->irq) {
   		if (ad1816->ih)
			bus_teardown_intr(dev, ad1816->irq, ad1816->ih);
		bus_release_resource(dev, SYS_RES_IRQ, ad1816->irq_rid, ad1816->irq);
		ad1816->irq = NULL;
    	}
    	if (ad1816->drq1) {
		isa_dma_release(rman_get_start(ad1816->drq1));
		bus_release_resource(dev, SYS_RES_DRQ, ad1816->drq1_rid, ad1816->drq1);
		ad1816->drq1 = NULL;
    	}
    	if (ad1816->drq2) {
		isa_dma_release(rman_get_start(ad1816->drq2));
		bus_release_resource(dev, SYS_RES_DRQ, ad1816->drq2_rid, ad1816->drq2);
		ad1816->drq2 = NULL;
    	}
    	if (ad1816->io_base) {
		bus_release_resource(dev, SYS_RES_IOPORT, ad1816->io_rid, ad1816->io_base);
		ad1816->io_base = NULL;
    	}
    	if (ad1816->parent_dmat) {
		bus_dma_tag_destroy(ad1816->parent_dmat);
		ad1816->parent_dmat = 0;
    	}
	if (ad1816->lock)
		snd_mtxfree(ad1816->lock);

     	free(ad1816, M_DEVBUF);
}