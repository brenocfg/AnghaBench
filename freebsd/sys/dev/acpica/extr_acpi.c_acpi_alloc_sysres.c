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
typedef  int u_int ;
struct rman {int dummy; } ;
struct resource {int dummy; } ;
typedef  int rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int RF_ACTIVE ; 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_MEMORY 128 
 struct rman acpi_rman_io ; 
 struct rman acpi_rman_mem ; 
 scalar_t__ bus_activate_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  rman_release_resource (struct resource*) ; 
 struct resource* rman_reserve_resource (struct rman*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_rid (struct resource*,int) ; 

struct resource *
acpi_alloc_sysres(device_t child, int type, int *rid, rman_res_t start,
    rman_res_t end, rman_res_t count, u_int flags)
{
    struct rman *rm;
    struct resource *res;

    switch (type) {
    case SYS_RES_IOPORT:
	rm = &acpi_rman_io;
	break;
    case SYS_RES_MEMORY:
	rm = &acpi_rman_mem;
	break;
    default:
	return (NULL);
    }

    KASSERT(start + count - 1 == end, ("wildcard resource range"));
    res = rman_reserve_resource(rm, start, end, count, flags & ~RF_ACTIVE,
	child);
    if (res == NULL)
	return (NULL);

    rman_set_rid(res, *rid);

    /* If requested, activate the resource using the parent's method. */
    if (flags & RF_ACTIVE)
	if (bus_activate_resource(child, type, *rid, res) != 0) {
	    rman_release_resource(res);
	    return (NULL);
	}

    return (res);
}