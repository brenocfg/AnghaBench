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
struct resource_map_request {scalar_t__ offset; scalar_t__ length; int /*<<< orphan*/  memattr; int /*<<< orphan*/  size; } ;
struct resource_map {int /*<<< orphan*/ * r_vaddr; scalar_t__ r_bushandle; scalar_t__ r_size; int /*<<< orphan*/  r_bustag; } ;
struct resource {int dummy; } ;
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_space_handle_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int RF_ACTIVE ; 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  X86_BUS_SPACE_IO ; 
 int /*<<< orphan*/  X86_BUS_SPACE_MEM ; 
 int /*<<< orphan*/  bcopy (struct resource_map_request*,struct resource_map_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_mapdev_attr (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_init_map_request (struct resource_map_request*) ; 
 scalar_t__ rman_get_end (struct resource*) ; 
 int rman_get_flags (struct resource*) ; 
 scalar_t__ rman_get_size (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 

__attribute__((used)) static int
nexus_map_resource(device_t bus, device_t child, int type, struct resource *r,
    struct resource_map_request *argsp, struct resource_map *map)
{
	struct resource_map_request args;
	rman_res_t end, length, start;

	/* Resources must be active to be mapped. */
	if (!(rman_get_flags(r) & RF_ACTIVE))
		return (ENXIO);

	/* Mappings are only supported on I/O and memory resources. */
	switch (type) {
	case SYS_RES_IOPORT:
	case SYS_RES_MEMORY:
		break;
	default:
		return (EINVAL);
	}

	resource_init_map_request(&args);
	if (argsp != NULL)
		bcopy(argsp, &args, imin(argsp->size, args.size));
	start = rman_get_start(r) + args.offset;
	if (args.length == 0)
		length = rman_get_size(r);
	else
		length = args.length;
	end = start + length - 1;
	if (start > rman_get_end(r) || start < rman_get_start(r))
		return (EINVAL);
	if (end > rman_get_end(r) || end < start)
		return (EINVAL);

	/*
	 * If this is a memory resource, map it into the kernel.
	 */
	switch (type) {
	case SYS_RES_IOPORT:
		map->r_bushandle = start;
		map->r_bustag = X86_BUS_SPACE_IO;
		map->r_size = length;
		map->r_vaddr = NULL;
		break;
	case SYS_RES_MEMORY:
		map->r_vaddr = pmap_mapdev_attr(start, length, args.memattr);
		map->r_bustag = X86_BUS_SPACE_MEM;
		map->r_size = length;

		/*
		 * The handle is the virtual address.
		 */
		map->r_bushandle = (bus_space_handle_t)map->r_vaddr;
		break;
	}
	return (0);
}