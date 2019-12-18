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
typedef  int /*<<< orphan*/  u_int32_t ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int SYS_RES_IOPORT ; 
 int SYS_RES_MEMORY ; 
 int /*<<< orphan*/  pmap_unmapdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rman_deactivate_resource (struct resource*) ; 
 int /*<<< orphan*/  rman_get_size (struct resource*) ; 
 scalar_t__ rman_get_virtual (struct resource*) ; 

__attribute__((used)) static int
unin_chip_deactivate_resource(device_t bus, device_t child, int type, int rid,
			      struct resource *res)
{
        /*
         * If this is a memory resource, unmap it.
         */
        if ((type == SYS_RES_MEMORY) || (type == SYS_RES_IOPORT)) {
		u_int32_t psize;
		
		psize = rman_get_size(res);
		pmap_unmapdev((vm_offset_t)rman_get_virtual(res), psize);
	}

	return (rman_deactivate_resource(res));
}