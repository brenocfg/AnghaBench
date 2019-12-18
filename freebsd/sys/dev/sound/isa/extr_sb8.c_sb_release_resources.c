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
struct sb_info {scalar_t__ parent_dmat; int /*<<< orphan*/ * io_base; int /*<<< orphan*/ * drq; int /*<<< orphan*/ * irq; scalar_t__ ih; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  free (struct sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_dma_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sb_release_resources(struct sb_info *sb, device_t dev)
{
    	if (sb->irq) {
    		if (sb->ih)
			bus_teardown_intr(dev, sb->irq, sb->ih);
 		bus_release_resource(dev, SYS_RES_IRQ, 0, sb->irq);
		sb->irq = NULL;
    	}
    	if (sb->drq) {
		isa_dma_release(rman_get_start(sb->drq));
		bus_release_resource(dev, SYS_RES_DRQ, 0, sb->drq);
		sb->drq = NULL;
    	}
    	if (sb->io_base) {
		bus_release_resource(dev, SYS_RES_IOPORT, 0, sb->io_base);
		sb->io_base = NULL;
    	}
    	if (sb->parent_dmat) {
		bus_dma_tag_destroy(sb->parent_dmat);
		sb->parent_dmat = 0;
    	}
     	free(sb, M_DEVBUF);
}