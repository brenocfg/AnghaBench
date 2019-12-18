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
struct quicc_device {int /*<<< orphan*/  qd_rlist; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int EINVAL ; 
 struct quicc_device* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int,int) ; 

int
quicc_bus_get_resource(device_t dev, device_t child, int type, int rid,
    rman_res_t *startp, rman_res_t *countp)
{
	struct quicc_device *qd;
	struct resource_list_entry *rle;

	if (device_get_parent(child) != dev)
		return (EINVAL);

	qd = device_get_ivars(child);
	rle = resource_list_find(&qd->qd_rlist, type, rid);
	if (rle == NULL)
		return (EINVAL);

	if (startp != NULL)
		*startp = rle->start;
	if (countp != NULL)
		*countp = rle->count;
	return (0);
}