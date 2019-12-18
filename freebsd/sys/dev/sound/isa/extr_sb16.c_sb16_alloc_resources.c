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
struct sb_info {void* drq1; void* drq2; int /*<<< orphan*/  bufsize; void* irq; void* io_base; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int SD_F_SIMPLEX ; 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_dma_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_dmainit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pcm_getflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_setflags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_get_start (void*) ; 

__attribute__((used)) static int
sb16_alloc_resources(struct sb_info *sb, device_t dev)
{
	int rid;

	rid = 0;
	if (!sb->io_base)
    		sb->io_base = bus_alloc_resource_any(dev, SYS_RES_IOPORT,
			&rid, RF_ACTIVE);

	rid = 0;
	if (!sb->irq)
    		sb->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
			RF_ACTIVE);

	rid = 0;
	if (!sb->drq1)
    		sb->drq1 = bus_alloc_resource_any(dev, SYS_RES_DRQ, &rid,
			RF_ACTIVE);

	rid = 1;
	if (!sb->drq2)
        	sb->drq2 = bus_alloc_resource_any(dev, SYS_RES_DRQ, &rid,
			RF_ACTIVE);

    	if (sb->io_base && sb->drq1 && sb->irq) {
		isa_dma_acquire(rman_get_start(sb->drq1));
		isa_dmainit(rman_get_start(sb->drq1), sb->bufsize);

		if (sb->drq2) {
			isa_dma_acquire(rman_get_start(sb->drq2));
			isa_dmainit(rman_get_start(sb->drq2), sb->bufsize);
		} else {
			sb->drq2 = sb->drq1;
			pcm_setflags(dev, pcm_getflags(dev) | SD_F_SIMPLEX);
		}
		return 0;
	} else return ENXIO;
}