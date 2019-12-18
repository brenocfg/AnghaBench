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
struct fdc_data {int* ridio; int* ioff; int rid_irq; int /*<<< orphan*/ * res_irq; int /*<<< orphan*/  iot; int /*<<< orphan*/ * ioh; struct resource** resio; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int FDC_MAXREG ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 

__attribute__((used)) static int
fdc_pccard_alloc_resources(device_t dev, struct fdc_data *fdc)
{
	struct resource *res;
	int rid, i;

	rid = 0;
	res = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &rid, RF_ACTIVE);
	if (res == NULL) {
		device_printf(dev, "cannot alloc I/O port range\n");
		return (ENXIO);
	}
	for (i = 0; i < FDC_MAXREG; i++) {
		fdc->resio[i] = res;
		fdc->ridio[i] = rid;
		fdc->ioff[i] = i;
		fdc->ioh[i] = rman_get_bushandle(res);
	}
	fdc->iot = rman_get_bustag(res);

	fdc->rid_irq = 0;
	fdc->res_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &fdc->rid_irq,
	    RF_ACTIVE | RF_SHAREABLE);
	if (fdc->res_irq == NULL) {
		device_printf(dev, "cannot reserve interrupt line\n");
		return (ENXIO);
	}
	return (0);
}