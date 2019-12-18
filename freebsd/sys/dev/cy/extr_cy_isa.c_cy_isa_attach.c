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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_TTY ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,void**) ; 
 void* cyattach_common (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cyintr ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 void* rman_get_virtual (struct resource*) ; 

__attribute__((used)) static int
cy_isa_attach(device_t dev)
{
	struct resource *irq_res, *mem_res;
	void *irq_cookie, *vaddr, *vsc;
	int irq_rid, mem_rid;

	irq_res = NULL;
	mem_res = NULL;

	mem_rid = 0;
	mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &mem_rid,
	    RF_ACTIVE);
	if (mem_res == NULL) {
		device_printf(dev, "memory resource allocation failed\n");
		goto fail;
	}
	vaddr = rman_get_virtual(mem_res);

	vsc = cyattach_common(vaddr, 0);
	if (vsc == NULL) {
		device_printf(dev, "no ports found!\n");
		goto fail;
	}

	irq_rid = 0;
	irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &irq_rid,
	    RF_SHAREABLE | RF_ACTIVE);
	if (irq_res == NULL) {
		device_printf(dev, "interrupt resource allocation failed\n");
		goto fail;
	}
	if (bus_setup_intr(dev, irq_res, INTR_TYPE_TTY, 
	    cyintr, NULL, vsc, &irq_cookie) != 0) {	    
		device_printf(dev, "interrupt setup failed\n");
		goto fail;
	}

	return (0);

fail:
	if (irq_res != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, irq_rid, irq_res);
	if (mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, mem_rid, mem_res);
	return (ENXIO);
}