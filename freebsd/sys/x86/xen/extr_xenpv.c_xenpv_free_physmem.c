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
typedef  scalar_t__ vm_paddr_t ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 size_t rman_get_size (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  vm_phys_fictitious_unreg_range (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
xenpv_free_physmem(device_t dev, device_t child, int res_id, struct resource *res)
{
	vm_paddr_t phys_addr;
	size_t size;

	phys_addr = rman_get_start(res);
	size = rman_get_size(res);

	vm_phys_fictitious_unreg_range(phys_addr, phys_addr + size);
	return (bus_release_resource(child, SYS_RES_MEMORY, res_id, res));
}