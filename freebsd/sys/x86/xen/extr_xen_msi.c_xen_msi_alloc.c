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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  first_msi_irq ; 
 scalar_t__ msi_last_irq ; 
 int /*<<< orphan*/  msi_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nexus_add_irq (int) ; 
 scalar_t__ num_msi_irqs ; 
 int xen_register_msi (int /*<<< orphan*/ ,int,int) ; 

int
xen_msi_alloc(device_t dev, int count, int maxcount, int *irqs)
{
	int i, ret = 0;

	mtx_lock(&msi_lock);

	/* If we would exceed the max, give up. */
	if (msi_last_irq + count > num_msi_irqs) {
		mtx_unlock(&msi_lock);
		return (ENXIO);
	}

	/* Allocate MSI vectors */
	for (i = 0; i < count; i++)
		irqs[i] = first_msi_irq + msi_last_irq++;

	mtx_unlock(&msi_lock);

	ret = xen_register_msi(dev, irqs[0], count);
	if (ret != 0)
		return (ret);

	for (i = 0; i < count; i++)
		nexus_add_irq(irqs[i]);

	return (0);
}