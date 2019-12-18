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

/* Variables and functions */
 int SYS_RES_IOPORT ; 
 int SYS_RES_MEMORY ; 
 int bus_generic_deactivate_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  pmap_unmapdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rman_deactivate_resource (struct resource*) ; 
 int /*<<< orphan*/  rman_get_size (struct resource*) ; 
 scalar_t__ rman_get_virtual (struct resource*) ; 

__attribute__((used)) static int
ofw_pci_deactivate_resource(device_t bus, device_t child, int type, int rid,
    struct resource *res)
{
	vm_size_t psize;

	if (type != SYS_RES_IOPORT && type != SYS_RES_MEMORY) {
		return (bus_generic_deactivate_resource(bus, child, type, rid,
		    res));
	}

	psize = rman_get_size(res);
	pmap_unmapdev((vm_offset_t)rman_get_virtual(res), psize);

	return (rman_deactivate_resource(res));
}