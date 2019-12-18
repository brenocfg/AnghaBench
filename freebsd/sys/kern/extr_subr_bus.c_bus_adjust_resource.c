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
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  TYPE_1__* device_t ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int BUS_ADJUST_RESOURCE (int /*<<< orphan*/ *,TYPE_1__*,int,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 

int
bus_adjust_resource(device_t dev, int type, struct resource *r, rman_res_t start,
    rman_res_t end)
{
	if (dev->parent == NULL)
		return (EINVAL);
	return (BUS_ADJUST_RESOURCE(dev->parent, dev, type, r, start, end));
}