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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct resource_list {int dummy; } ;
struct resource {int dummy; } ;
struct isa_device {struct resource_list id_resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct isa_device* DEVTOISA (int /*<<< orphan*/ ) ; 
 int ISA_PNP_NIRQ ; 
 int ISA_PNP_NMEM ; 
 int ISA_PNP_NPORT ; 
 scalar_t__ RMAN_IS_DEFAULT_RANGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SYS_RES_IOPORT 130 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_list_add (struct resource_list*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* resource_list_alloc (struct resource_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * resource_list_find (struct resource_list*,int,int) ; 

struct resource *
isa_alloc_resource(device_t bus, device_t child, int type, int *rid,
    u_long start, u_long end, u_long count, u_int flags)
{
	struct isa_device* idev = DEVTOISA(child);
	struct resource_list *rl = &idev->id_resources;
	int isdefault, passthrough, rids;

	isdefault = RMAN_IS_DEFAULT_RANGE(start, end) ? 1 : 0;
	passthrough = (device_get_parent(child) != bus) ? 1 : 0;

	if (!passthrough && !isdefault &&
	    resource_list_find(rl, type, *rid) == NULL) {
		switch (type) {
		case SYS_RES_IOPORT:	rids = ISA_PNP_NPORT; break;
		case SYS_RES_IRQ:	rids = ISA_PNP_NIRQ; break;
		case SYS_RES_MEMORY:	rids = ISA_PNP_NMEM; break;
		default:		rids = 0; break;
		}
		if (*rid < 0 || *rid >= rids)
			return (NULL);

		resource_list_add(rl, type, *rid, start, end, count);
	}

	return (resource_list_alloc(rl, bus, child, type, rid, start, end,
	    count, flags));
}