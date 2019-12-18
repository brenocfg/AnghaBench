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
typedef  int /*<<< orphan*/  u_long ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int KBDC_RID_KBD ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int atkbd_probe_unit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bootverbose ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int device_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 

__attribute__((used)) static int
atkbdprobe(device_t dev)
{
	struct resource *res;
	u_long irq;
	int flags;
	int rid;

	device_set_desc(dev, "AT Keyboard");

	/* obtain parameters */
	flags = device_get_flags(dev);

	/* see if IRQ is available */
	rid = KBDC_RID_KBD;
	res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, RF_ACTIVE);
	if (res == NULL) {
		if (bootverbose)
			device_printf(dev, "unable to allocate IRQ\n");
		return ENXIO;
	}
	irq = rman_get_start(res);
	bus_release_resource(dev, SYS_RES_IRQ, rid, res);

	/* probe the device */
	return atkbd_probe_unit(dev, irq, flags);
}