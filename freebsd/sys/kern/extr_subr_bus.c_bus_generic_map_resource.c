#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource_map_request {int dummy; } ;
struct resource_map {int dummy; } ;
struct resource {int dummy; } ;
typedef  TYPE_1__* device_t ;
struct TYPE_5__ {scalar_t__ parent; } ;

/* Variables and functions */
 int BUS_MAP_RESOURCE (scalar_t__,TYPE_1__*,int,struct resource*,struct resource_map_request*,struct resource_map*) ; 
 int EINVAL ; 

int
bus_generic_map_resource(device_t dev, device_t child, int type,
    struct resource *r, struct resource_map_request *args,
    struct resource_map *map)
{
	/* Propagate up the bus hierarchy until someone handles it. */
	if (dev->parent)
		return (BUS_MAP_RESOURCE(dev->parent, child, type, r, args,
		    map));
	return (EINVAL);
}