#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
typedef  TYPE_1__* device_t ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int BUS_DEACTIVATE_RESOURCE (int /*<<< orphan*/ *,TYPE_1__*,int,int,struct resource*) ; 
 int EINVAL ; 

int
bus_deactivate_resource(device_t dev, int type, int rid, struct resource *r)
{
	if (dev->parent == NULL)
		return (EINVAL);
	return (BUS_DEACTIVATE_RESOURCE(dev->parent, dev, type, rid, r));
}