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
struct ppb_device {void (* intr_hook ) (void*) ;void* intr_arg; } ;
struct ppb_data {int /*<<< orphan*/  ppc_lock; struct resource* ppc_irq_res; } ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ppb_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 struct ppb_device* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ppbus_setup_intr(device_t bus, device_t child, struct resource *r, int flags,
    driver_filter_t *filt, void (*ihand)(void *), void *arg, void **cookiep)
{
	struct ppb_device *ppbdev = device_get_ivars(child);
	struct ppb_data *ppb = DEVTOSOFTC(bus);

	/* We do not support filters. */
	if (filt != NULL || ihand == NULL)
		return (EINVAL);

	/* Can only attach handlers to the parent device's resource. */
	if (ppb->ppc_irq_res != r)
		return (EINVAL);

	mtx_lock(ppb->ppc_lock);
	ppbdev->intr_hook = ihand;
	ppbdev->intr_arg = arg;
	*cookiep = ppbdev;
	mtx_unlock(ppb->ppc_lock);

	return (0);
}