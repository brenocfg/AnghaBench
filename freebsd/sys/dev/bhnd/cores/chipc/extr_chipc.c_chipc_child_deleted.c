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
struct chipc_devinfo {int irq_mapped; int /*<<< orphan*/  irq; int /*<<< orphan*/  resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  bhnd_unmap_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct chipc_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct chipc_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
chipc_child_deleted(device_t dev, device_t child)
{
	struct chipc_devinfo *dinfo = device_get_ivars(child);

	if (dinfo != NULL) {
		/* Free the child's resource list */
		resource_list_free(&dinfo->resources);

		/* Unmap the child's IRQ */
		if (dinfo->irq_mapped) {
			bhnd_unmap_intr(dev, dinfo->irq);
			dinfo->irq_mapped = false;
		}

		free(dinfo, M_BHND);
	}

	device_set_ivars(child, NULL);
}