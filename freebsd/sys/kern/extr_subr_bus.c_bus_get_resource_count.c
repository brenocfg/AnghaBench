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
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_GET_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

rman_res_t
bus_get_resource_count(device_t dev, int type, int rid)
{
	rman_res_t start;
	rman_res_t count;
	int error;

	error = BUS_GET_RESOURCE(device_get_parent(dev), dev, type, rid,
	    &start, &count);
	if (error)
		return (0);
	return (count);
}