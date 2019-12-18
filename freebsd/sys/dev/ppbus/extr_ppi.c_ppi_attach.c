#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ppi_data {int /*<<< orphan*/  ppi_device; TYPE_1__* ppi_cdev; int /*<<< orphan*/  ppi_lock; scalar_t__ intr_resource; int /*<<< orphan*/  intr_cookie; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct ppi_data* si_drv1; } ;

/* Variables and functions */
 struct ppi_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_TTY ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  UID_ROOT ; 
 scalar_t__ bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppi_cdevsw ; 
 int /*<<< orphan*/  ppiintr ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
ppi_attach(device_t dev)
{
	struct ppi_data *ppi = DEVTOSOFTC(dev);
#ifdef PERIPH_1284
	int error, rid = 0;

	/* declare our interrupt handler */
	ppi->intr_resource = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (ppi->intr_resource) {
		/* register our interrupt handler */
		error = bus_setup_intr(dev, ppi->intr_resource,
		    INTR_TYPE_TTY | INTR_MPSAFE, NULL, ppiintr, dev,
		    &ppi->intr_cookie);
		if (error) {
			bus_release_resource(dev, SYS_RES_IRQ, rid,
			    ppi->intr_resource);
			device_printf(dev,
			    "Unable to register interrupt handler\n");
			return (error);
		}
	}
#endif /* PERIPH_1284 */

	sx_init(&ppi->ppi_lock, "ppi");
	ppi->ppi_cdev = make_dev(&ppi_cdevsw, device_get_unit(dev),
		 UID_ROOT, GID_WHEEL,
		 0600, "ppi%d", device_get_unit(dev));
	if (ppi->ppi_cdev == NULL) {
		device_printf(dev, "Failed to create character device\n");
		return (ENXIO);
	}
	ppi->ppi_cdev->si_drv1 = ppi;
	ppi->ppi_device = dev;

	return (0);
}