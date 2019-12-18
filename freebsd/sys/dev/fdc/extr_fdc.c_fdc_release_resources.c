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
struct resource {int dummy; } ;
struct fdc_data {struct resource* res_drq; int /*<<< orphan*/  rid_drq; struct resource** resio; int /*<<< orphan*/ * ridio; struct resource* res_irq; int /*<<< orphan*/  rid_irq; int /*<<< orphan*/ * fdc_intr; int /*<<< orphan*/  fdc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int FDC_MAXREG ; 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ *) ; 

void
fdc_release_resources(struct fdc_data *fdc)
{
	device_t dev;
	struct resource *last;
	int i;

	dev = fdc->fdc_dev;
	if (fdc->fdc_intr)
		bus_teardown_intr(dev, fdc->res_irq, fdc->fdc_intr);
	fdc->fdc_intr = NULL;
	if (fdc->res_irq != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, fdc->rid_irq,
		    fdc->res_irq);
	fdc->res_irq = NULL;
	last = NULL;
	for (i = 0; i < FDC_MAXREG; i++) {
		if (fdc->resio[i] != NULL && fdc->resio[i] != last) {
			bus_release_resource(dev, SYS_RES_IOPORT,
			    fdc->ridio[i], fdc->resio[i]);
			last = fdc->resio[i];
			fdc->resio[i] = NULL;
		}
	}
	if (fdc->res_drq != NULL)
		bus_release_resource(dev, SYS_RES_DRQ, fdc->rid_drq,
		    fdc->res_drq);
	fdc->res_drq = NULL;
}