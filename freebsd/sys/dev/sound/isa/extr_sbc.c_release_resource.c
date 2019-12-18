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
struct sbc_softc {int /*<<< orphan*/ ** irq; int /*<<< orphan*/ * irq_rid; int /*<<< orphan*/  dev; int /*<<< orphan*/ ** ih; int /*<<< orphan*/ ** drq; int /*<<< orphan*/ * drq_rid; int /*<<< orphan*/ ** io; int /*<<< orphan*/ * io_rid; } ;

/* Variables and functions */
 int DRQ_MAX ; 
 int IO_MAX ; 
 int IRQ_MAX ; 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
release_resource(struct sbc_softc *scp)
{
	int i;

	for (i = 0 ; i < IO_MAX ; i++) {
		if (scp->io[i] != NULL) {
			bus_release_resource(scp->dev, SYS_RES_IOPORT, scp->io_rid[i], scp->io[i]);
			scp->io[i] = NULL;
		}
	}
	for (i = 0 ; i < DRQ_MAX ; i++) {
		if (scp->drq[i] != NULL) {
			bus_release_resource(scp->dev, SYS_RES_DRQ, scp->drq_rid[i], scp->drq[i]);
			scp->drq[i] = NULL;
		}
	}
	for (i = 0 ; i < IRQ_MAX ; i++) {
		if (scp->irq[i] != NULL) {
			if (scp->ih[i] != NULL)
				bus_teardown_intr(scp->dev, scp->irq[i], scp->ih[i]);
			scp->ih[i] = NULL;
			bus_release_resource(scp->dev, SYS_RES_IRQ, scp->irq_rid[i], scp->irq[i]);
			scp->irq[i] = NULL;
		}
	}
	return (0);
}