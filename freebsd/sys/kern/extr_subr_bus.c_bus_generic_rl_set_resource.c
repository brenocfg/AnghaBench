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
struct resource_list {int dummy; } ;
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct resource_list* BUS_GET_RESOURCE_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  resource_list_add (struct resource_list*,int,int,scalar_t__,scalar_t__,scalar_t__) ; 

int
bus_generic_rl_set_resource(device_t dev, device_t child, int type, int rid,
    rman_res_t start, rman_res_t count)
{
	struct resource_list *		rl = NULL;

	rl = BUS_GET_RESOURCE_LIST(dev, child);
	if (!rl)
		return (EINVAL);

	resource_list_add(rl, type, rid, start, (start + count - 1), count);

	return (0);
}