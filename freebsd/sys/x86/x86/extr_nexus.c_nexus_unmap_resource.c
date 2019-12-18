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
struct resource_map {int /*<<< orphan*/  r_size; int /*<<< orphan*/  r_vaddr; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  pmap_unmapdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nexus_unmap_resource(device_t bus, device_t child, int type, struct resource *r,
    struct resource_map *map)
{
	
	/*
	 * If this is a memory resource, unmap it.
	 */
	switch (type) {
	case SYS_RES_MEMORY:
		pmap_unmapdev((vm_offset_t)map->r_vaddr, map->r_size);
		/* FALLTHROUGH */
	case SYS_RES_IOPORT:
		break;
	default:
		return (EINVAL);
	}
	return (0);
}