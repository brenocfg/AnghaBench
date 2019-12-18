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
struct sbc_softc {int* io_rid; int* drq_rid; int* irq_rid; scalar_t__* irq_alloced; int /*<<< orphan*/ ** irq; int /*<<< orphan*/  dev; scalar_t__* drq_alloced; int /*<<< orphan*/ ** drq; scalar_t__* io_alloced; int /*<<< orphan*/ ** io; } ;

/* Variables and functions */
 int DRQ_MAX ; 
 int IO_MAX ; 
 int IRQ_MAX ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * io_range ; 

__attribute__((used)) static int
alloc_resource(struct sbc_softc *scp)
{
	int i;

	for (i = 0 ; i < IO_MAX ; i++) {
		if (scp->io[i] == NULL) {
			scp->io_rid[i] = i;
			scp->io[i] = bus_alloc_resource_anywhere(scp->dev,
								 SYS_RES_IOPORT,
								 &scp->io_rid[i],
								io_range[i],
								RF_ACTIVE);
			if (i == 0 && scp->io[i] == NULL)
				return (1);
			scp->io_alloced[i] = 0;
		}
	}
	for (i = 0 ; i < DRQ_MAX ; i++) {
		if (scp->drq[i] == NULL) {
			scp->drq_rid[i] = i;
			scp->drq[i] = bus_alloc_resource_any(scp->dev,
							     SYS_RES_DRQ,
							     &scp->drq_rid[i],
							     RF_ACTIVE);
			if (i == 0 && scp->drq[i] == NULL)
				return (1);
			scp->drq_alloced[i] = 0;
		}
	}
	for (i = 0 ; i < IRQ_MAX ; i++) {
	 	if (scp->irq[i] == NULL) {
			scp->irq_rid[i] = i;
			scp->irq[i] = bus_alloc_resource_any(scp->dev,
							     SYS_RES_IRQ,
							     &scp->irq_rid[i],
							     RF_ACTIVE);
			if (i == 0 && scp->irq[i] == NULL)
				return (1);
			scp->irq_alloced[i] = 0;
		}
	}
	return (0);
}