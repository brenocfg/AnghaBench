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
struct ad1816_info {int /*<<< orphan*/  bufsize; void* drq2; void* drq1; void* irq; void* io_base; int /*<<< orphan*/  drq2_rid; int /*<<< orphan*/  drq1_rid; int /*<<< orphan*/  irq_rid; int /*<<< orphan*/  io_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RF_ACTIVE ; 
 int SD_F_SIMPLEX ; 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_dma_acquire (int) ; 
 int /*<<< orphan*/  isa_dmainit (int,int /*<<< orphan*/ ) ; 
 int pcm_getflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_setflags (int /*<<< orphan*/ ,int) ; 
 int rman_get_start (void*) ; 

__attribute__((used)) static int
ad1816_alloc_resources(struct ad1816_info *ad1816, device_t dev)
{
    	int ok = 1, pdma, rdma;

	if (!ad1816->io_base)
    		ad1816->io_base = bus_alloc_resource_any(dev, 
			SYS_RES_IOPORT, &ad1816->io_rid, RF_ACTIVE);
	if (!ad1816->irq)
    		ad1816->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ,
			&ad1816->irq_rid, RF_ACTIVE);
	if (!ad1816->drq1)
    		ad1816->drq1 = bus_alloc_resource_any(dev, SYS_RES_DRQ,
			&ad1816->drq1_rid, RF_ACTIVE);
    	if (!ad1816->drq2)
        	ad1816->drq2 = bus_alloc_resource_any(dev, SYS_RES_DRQ, 
			&ad1816->drq2_rid, RF_ACTIVE);

    	if (!ad1816->io_base || !ad1816->drq1 || !ad1816->irq) ok = 0;

	if (ok) {
		pdma = rman_get_start(ad1816->drq1);
		isa_dma_acquire(pdma);
		isa_dmainit(pdma, ad1816->bufsize);
		if (ad1816->drq2) {
			rdma = rman_get_start(ad1816->drq2);
			isa_dma_acquire(rdma);
			isa_dmainit(rdma, ad1816->bufsize);
		} else
			rdma = pdma;
    		if (pdma == rdma)
			pcm_setflags(dev, pcm_getflags(dev) | SD_F_SIMPLEX);
	}

    	return ok;
}