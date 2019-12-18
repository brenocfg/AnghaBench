#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/ * driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  TYPE_1__* device_t ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int BUS_SETUP_INTR (int /*<<< orphan*/ *,TYPE_1__*,struct resource*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,void**) ; 
 int EINVAL ; 
 int INTR_MPSAFE ; 
 int /*<<< orphan*/  device_printf (TYPE_1__*,char*) ; 

int
bus_setup_intr(device_t dev, struct resource *r, int flags,
    driver_filter_t filter, driver_intr_t handler, void *arg, void **cookiep)
{
	int error;

	if (dev->parent == NULL)
		return (EINVAL);
	error = BUS_SETUP_INTR(dev->parent, dev, r, flags, filter, handler,
	    arg, cookiep);
	if (error != 0)
		return (error);
	if (handler != NULL && !(flags & INTR_MPSAFE))
		device_printf(dev, "[GIANT-LOCKED]\n");
	return (0);
}