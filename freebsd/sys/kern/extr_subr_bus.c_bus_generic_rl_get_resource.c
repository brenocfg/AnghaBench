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
struct resource_list_entry {int /*<<< orphan*/  count; int /*<<< orphan*/  start; } ;
struct resource_list {int dummy; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct resource_list* BUS_GET_RESOURCE_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOENT ; 
 struct resource_list_entry* resource_list_find (struct resource_list*,int,int) ; 

int
bus_generic_rl_get_resource(device_t dev, device_t child, int type, int rid,
    rman_res_t *startp, rman_res_t *countp)
{
	struct resource_list *		rl = NULL;
	struct resource_list_entry *	rle = NULL;

	rl = BUS_GET_RESOURCE_LIST(dev, child);
	if (!rl)
		return (EINVAL);

	rle = resource_list_find(rl, type, rid);
	if (!rle)
		return (ENOENT);

	if (startp)
		*startp = rle->start;
	if (countp)
		*countp = rle->count;

	return (0);
}