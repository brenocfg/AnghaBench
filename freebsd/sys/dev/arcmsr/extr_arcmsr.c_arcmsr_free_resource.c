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
struct AdapterControlBlock {int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/  dm_segs_dmat; int /*<<< orphan*/  srb_dmat; int /*<<< orphan*/  srb_dmamap; int /*<<< orphan*/ * ioctl_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void arcmsr_free_resource(struct AdapterControlBlock *acb)
{
	/* remove the control device */
	if(acb->ioctl_dev != NULL) {
		destroy_dev(acb->ioctl_dev);
	}
	bus_dmamap_unload(acb->srb_dmat, acb->srb_dmamap);
	bus_dmamap_destroy(acb->srb_dmat, acb->srb_dmamap);
	bus_dma_tag_destroy(acb->srb_dmat);
	bus_dma_tag_destroy(acb->dm_segs_dmat);
	bus_dma_tag_destroy(acb->parent_dmat);
}