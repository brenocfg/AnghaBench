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
typedef  int /*<<< orphan*/  vm_paddr_t ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int SYS_RES_IOPORT ; 
 int SYS_RES_MEMORY ; 
 void* pmap_mapdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rman_activate_resource (struct resource*) ; 
 int /*<<< orphan*/  rman_get_size (struct resource*) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_virtual (struct resource*,void*) ; 

__attribute__((used)) static int
xlp_simplebus_activate_resource(device_t bus, device_t child, int type, int rid,
    struct resource *r)
{
	void *vaddr;
	vm_paddr_t paddr;
	vm_size_t psize;

	/*
	 * If this is a memory resource, use pmap_mapdev to map it.
	 */
	if (type == SYS_RES_MEMORY || type == SYS_RES_IOPORT) {
		paddr = rman_get_start(r);
		psize = rman_get_size(r);
		vaddr = pmap_mapdev(paddr, psize);

		rman_set_virtual(r, vaddr);
		rman_set_bushandle(r, (bus_space_handle_t)(uintptr_t)vaddr);
	}

	return (rman_activate_resource(r));
}