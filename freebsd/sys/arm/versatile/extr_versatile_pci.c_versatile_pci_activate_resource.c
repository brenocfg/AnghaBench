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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_ACTIVATE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int ENXIO ; 
#define  SYS_RES_IOPORT 130 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int /*<<< orphan*/  pmap_mapdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rman_activate_resource (struct resource*) ; 
 int /*<<< orphan*/  rman_get_size (struct resource*) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_bustag (struct resource*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
versatile_pci_activate_resource(device_t bus, device_t child, int type, int rid,
    struct resource *r)
{
	vm_offset_t vaddr;
	int res;

	switch(type) {
	case SYS_RES_MEMORY:
	case SYS_RES_IOPORT:
		vaddr = (vm_offset_t)pmap_mapdev(rman_get_start(r),
				rman_get_size(r));
		rman_set_bushandle(r, vaddr);
		rman_set_bustag(r, fdtbus_bs_tag);
		res = rman_activate_resource(r);
		break;
	case SYS_RES_IRQ:
		res = (BUS_ACTIVATE_RESOURCE(device_get_parent(bus),
		    child, type, rid, r));
		break;
	default:
		res = ENXIO;
		break;
	}

	return (res);
}