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
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct resource_list_entry {int start; int end; } ;
struct resource_list {int dummy; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct resource_list* BUS_GET_RESOURCE_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INRANGE (int,scalar_t__,scalar_t__) ; 
 int ISA_NDRQ ; 
 int ISA_NIRQ ; 
 int ISA_NMEM ; 
 int ISA_NPORT ; 
 int RMAN_IS_DEFAULT_RANGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SYS_RES_DRQ 131 
#define  SYS_RES_IOPORT 130 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ isa_io_base ; 
 scalar_t__ isa_io_limit ; 
 scalar_t__ isa_mem_base ; 
 scalar_t__ isa_mem_limit ; 
 int /*<<< orphan*/  resource_list_add (struct resource_list*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* resource_list_alloc (struct resource_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource_list_entry* resource_list_find (struct resource_list*,int,int) ; 

struct resource *
isa_alloc_resource(device_t bus, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	/*
	 * Consider adding a resource definition.
	 */
	int passthrough = (device_get_parent(child) != bus);
	int isdefault = RMAN_IS_DEFAULT_RANGE(start, end);
	struct resource_list *rl;
	struct resource_list_entry *rle;
	u_long base, limit;

	rl = BUS_GET_RESOURCE_LIST(bus, child);
	if (!passthrough && !isdefault) {
		rle = resource_list_find(rl, type, *rid);
		if (!rle) {
			if (*rid < 0)
				return (NULL);
			switch (type) {
			case SYS_RES_IRQ:
				if (*rid >= ISA_NIRQ)
					return (NULL);
				break;
			case SYS_RES_DRQ:
				if (*rid >= ISA_NDRQ)
					return (NULL);
				break;
			case SYS_RES_MEMORY:
				if (*rid >= ISA_NMEM)
					return (NULL);
				break;
			case SYS_RES_IOPORT:
				if (*rid >= ISA_NPORT)
					return (NULL);
				break;
			default:
				return (NULL);
			}
			resource_list_add(rl, type, *rid, start, end, count);
		}
	}

	/*
	 * Sanity check if the resource in the respective entry is fully
	 * mapped and specified and its type allocable. A driver could
	 * have added an out of range resource on its own.
	 */
	if (!passthrough) {
		if ((rle = resource_list_find(rl, type, *rid)) == NULL)
			return (NULL);
		base = limit = 0;
		switch (type) {
		case SYS_RES_MEMORY:
			base = isa_mem_base;
			limit = base + isa_mem_limit;
			break;
		case SYS_RES_IOPORT:
			base = isa_io_base;
			limit = base + isa_io_limit;
			break;
		case SYS_RES_IRQ:
			if (rle->start != rle->end || rle->start <= 7)
				return (NULL);
			break;
		case SYS_RES_DRQ:
			break;
		default:
			return (NULL);
		}
		if (type == SYS_RES_MEMORY || type == SYS_RES_IOPORT) {
			if (!INRANGE(rle->start, base, limit) ||
			    !INRANGE(rle->end, base, limit))
				return (NULL);
		}
	}

	return (resource_list_alloc(rl, bus, child, type, rid, start, end,
	    count, flags));
}