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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  panic (char*,int,int) ; 

__attribute__((used)) static void
apic_add_resource(device_t dev, int rid, vm_paddr_t base, size_t length)
{
	int error;

	error = bus_set_resource(dev, SYS_RES_MEMORY, rid, base, length);
	if (error)
		panic("apic_add_resource: resource %d failed set with %d", rid,
		    error);
	bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_SHAREABLE);
}