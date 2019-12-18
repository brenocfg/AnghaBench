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
typedef  int /*<<< orphan*/  u_int ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  TYPE_1__* device_t ;
struct TYPE_5__ {scalar_t__ parent; } ;

/* Variables and functions */
 struct resource* BUS_ALLOC_RESOURCE (scalar_t__,TYPE_1__*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct resource *
bus_generic_alloc_resource(device_t dev, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	/* Propagate up the bus hierarchy until someone handles it. */
	if (dev->parent)
		return (BUS_ALLOC_RESOURCE(dev->parent, child, type, rid,
		    start, end, count, flags));
	return (NULL);
}