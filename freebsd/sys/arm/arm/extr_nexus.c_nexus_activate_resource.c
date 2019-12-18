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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_space_handle_t ;
typedef  scalar_t__ bus_size_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int SYS_RES_IOPORT ; 
 int SYS_RES_IRQ ; 
 int SYS_RES_MEMORY ; 
 int bus_space_map (void*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 void* fdtbus_bs_tag ; 
 int intr_activate_irq (int /*<<< orphan*/ ,struct resource*) ; 
 scalar_t__ pmap_mapdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rman_activate_resource (struct resource*) ; 
 int /*<<< orphan*/  rman_deactivate_resource (struct resource*) ; 
 scalar_t__ rman_get_size (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,scalar_t__) ; 
 int /*<<< orphan*/  rman_set_bustag (struct resource*,void*) ; 
 int /*<<< orphan*/  rman_set_virtual (struct resource*,void*) ; 

__attribute__((used)) static int
nexus_activate_resource(device_t bus, device_t child, int type, int rid,
    struct resource *r)
{
	int err;
	bus_addr_t paddr;
	bus_size_t psize;
	bus_space_handle_t vaddr;

	if ((err = rman_activate_resource(r)) != 0)
		return (err);

	/*
	 * If this is a memory resource, map it into the kernel.
	 */
	if (type == SYS_RES_MEMORY || type == SYS_RES_IOPORT) {
		paddr = (bus_addr_t)rman_get_start(r);
		psize = (bus_size_t)rman_get_size(r);
#ifdef FDT
		err = bus_space_map(fdtbus_bs_tag, paddr, psize, 0, &vaddr);
		if (err != 0) {
			rman_deactivate_resource(r);
			return (err);
		}
		rman_set_bustag(r, fdtbus_bs_tag);
#else
		vaddr = (bus_space_handle_t)pmap_mapdev((vm_offset_t)paddr,
		    (vm_size_t)psize);
		if (vaddr == 0) {
			rman_deactivate_resource(r);
			return (ENOMEM);
		}
		rman_set_bustag(r, (void *)1);
#endif
		rman_set_virtual(r, (void *)vaddr);
		rman_set_bushandle(r, vaddr);
		return (0);
	} else if (type == SYS_RES_IRQ) {
#ifdef INTRNG
		err = intr_activate_irq(child, r);
		if (err != 0) {
			rman_deactivate_resource(r);
			return (err);
		}
#endif
	}
	return (0);
}