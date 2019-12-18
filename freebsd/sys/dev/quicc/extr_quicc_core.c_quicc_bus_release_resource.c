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
struct resource_list_entry {int dummy; } ;
struct resource {int dummy; } ;
struct quicc_device {int /*<<< orphan*/  qd_rlist; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int EINVAL ; 
 struct quicc_device* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int,int) ; 

int
quicc_bus_release_resource(device_t dev, device_t child, int type, int rid,
    struct resource *res)
{
	struct quicc_device *qd;
	struct resource_list_entry *rle;

	if (device_get_parent(child) != dev)
		return (EINVAL);

	qd = device_get_ivars(child);
	rle = resource_list_find(&qd->qd_rlist, type, rid);
	return ((rle == NULL) ? EINVAL : 0);
}