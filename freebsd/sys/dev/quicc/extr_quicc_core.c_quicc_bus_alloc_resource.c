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
typedef  int /*<<< orphan*/  u_int ;
struct resource_list_entry {struct resource* res; scalar_t__ start; scalar_t__ count; } ;
struct resource {int dummy; } ;
struct quicc_device {int /*<<< orphan*/  qd_rman; int /*<<< orphan*/  qd_rlist; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RMAN_IS_DEFAULT_RANGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bs_be_tag ; 
 struct quicc_device* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int,int) ; 
 struct resource* rman_reserve_resource (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,scalar_t__) ; 
 int /*<<< orphan*/  rman_set_bustag (struct resource*,int /*<<< orphan*/ *) ; 

struct resource *
quicc_bus_alloc_resource(device_t dev, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct quicc_device *qd;
	struct resource_list_entry *rle;

	if (device_get_parent(child) != dev)
		return (NULL);

	/* We only support default allocations. */
	if (!RMAN_IS_DEFAULT_RANGE(start, end))
		return (NULL);

	qd = device_get_ivars(child);
	rle = resource_list_find(&qd->qd_rlist, type, *rid);
	if (rle == NULL)
		return (NULL);

	if (rle->res == NULL) {
		rle->res = rman_reserve_resource(qd->qd_rman, rle->start,
		    rle->start + rle->count - 1, rle->count, flags, child);
		if (rle->res != NULL) {
			rman_set_bustag(rle->res, &bs_be_tag);
			rman_set_bushandle(rle->res, rle->start);
		}
	}
	return (rle->res);
}