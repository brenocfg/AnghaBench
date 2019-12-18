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
struct ppi_data {int /*<<< orphan*/  ppi_lock; int /*<<< orphan*/ * intr_resource; int /*<<< orphan*/  intr_cookie; int /*<<< orphan*/  ppi_cdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ppi_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ppi_detach(device_t dev)
{
	struct ppi_data *ppi = DEVTOSOFTC(dev);

	destroy_dev(ppi->ppi_cdev);
#ifdef PERIPH_1284
	if (ppi->intr_resource != NULL) {
		bus_teardown_intr(dev, ppi->intr_resource, ppi->intr_cookie);
		bus_release_resource(dev, SYS_RES_IRQ, 0, ppi->intr_resource);
	}
#endif
	sx_destroy(&ppi->ppi_lock);
	return (0);
}