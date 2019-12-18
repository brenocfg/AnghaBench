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
typedef  scalar_t__ vm_offset_t ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int SYS_RES_IRQ ; 
 int SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bs_be_tag ; 
 int bus_activate_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 void* pmap_mapdev (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,scalar_t__) ; 
 int rman_activate_resource (struct resource*) ; 
 scalar_t__ rman_get_size (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_bustag (struct resource*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_set_virtual (struct resource*,void*) ; 

__attribute__((used)) static int
ps3bus_activate_resource(device_t bus, device_t child, int type, int rid,
    struct resource *res)
{
	void *p;

	if (type == SYS_RES_IRQ)
		return (bus_activate_resource(bus, type, rid, res));

	if (type == SYS_RES_MEMORY) {
		vm_offset_t start;

		start = (vm_offset_t) rman_get_start(res);

		if (bootverbose)
			printf("ps3 mapdev: start %zx, len %ld\n", start,
			       rman_get_size(res));

		p = pmap_mapdev(start, (vm_size_t) rman_get_size(res));
		if (p == NULL)
			return (ENOMEM);
		rman_set_virtual(res, p);
		rman_set_bustag(res, &bs_be_tag);
		rman_set_bushandle(res, (rman_res_t)p);
	}

	return (rman_activate_resource(res));
}