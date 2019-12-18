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
struct mss_info {scalar_t__ lock; scalar_t__ parent_dmat; int /*<<< orphan*/ * indir; int /*<<< orphan*/  indir_rid; int /*<<< orphan*/ * conf_base; int /*<<< orphan*/  conf_rid; int /*<<< orphan*/ * io_base; int /*<<< orphan*/  io_rid; int /*<<< orphan*/ * drq1; int /*<<< orphan*/  drq1_rid; int /*<<< orphan*/ * drq2; int /*<<< orphan*/  drq2_rid; int /*<<< orphan*/ * irq; int /*<<< orphan*/  irq_rid; scalar_t__ ih; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  free (struct mss_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_dma_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mtxfree (scalar_t__) ; 

__attribute__((used)) static void
mss_release_resources(struct mss_info *mss, device_t dev)
{
    	if (mss->irq) {
    		if (mss->ih)
			bus_teardown_intr(dev, mss->irq, mss->ih);
 		bus_release_resource(dev, SYS_RES_IRQ, mss->irq_rid,
				     mss->irq);
		mss->irq = NULL;
    	}
    	if (mss->drq2) {
		if (mss->drq2 != mss->drq1) {
			isa_dma_release(rman_get_start(mss->drq2));
			bus_release_resource(dev, SYS_RES_DRQ, mss->drq2_rid,
				     	mss->drq2);
		}
		mss->drq2 = NULL;
    	}
     	if (mss->drq1) {
		isa_dma_release(rman_get_start(mss->drq1));
		bus_release_resource(dev, SYS_RES_DRQ, mss->drq1_rid,
				     mss->drq1);
		mss->drq1 = NULL;
    	}
   	if (mss->io_base) {
		bus_release_resource(dev, SYS_RES_IOPORT, mss->io_rid,
				     mss->io_base);
		mss->io_base = NULL;
    	}
    	if (mss->conf_base) {
		bus_release_resource(dev, SYS_RES_IOPORT, mss->conf_rid,
				     mss->conf_base);
		mss->conf_base = NULL;
    	}
	if (mss->indir) {
		bus_release_resource(dev, SYS_RES_IOPORT, mss->indir_rid,
				     mss->indir);
		mss->indir = NULL;
	}
    	if (mss->parent_dmat) {
		bus_dma_tag_destroy(mss->parent_dmat);
		mss->parent_dmat = 0;
    	}
	if (mss->lock) snd_mtxfree(mss->lock);

     	free(mss, M_DEVBUF);
}