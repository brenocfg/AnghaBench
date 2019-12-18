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
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ VGA_MEM_BASE ; 
 scalar_t__ VGA_MEM_SIZE ; 
 struct resource* bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
vtvga_attach(device_t dev)
{
	struct resource *pseudo_phys_res;
	int res_id;

	res_id = 0;
	pseudo_phys_res = bus_alloc_resource(dev, SYS_RES_MEMORY,
	    &res_id, VGA_MEM_BASE, VGA_MEM_BASE + VGA_MEM_SIZE - 1,
	    VGA_MEM_SIZE, RF_ACTIVE);
	if (pseudo_phys_res == NULL)
		panic("Unable to reserve vt_vga memory");
	return (0);
}