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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int RF_ACTIVE ; 
 int bus_deactivate_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int rman_get_flags (struct resource*) ; 
 int rman_release_resource (struct resource*) ; 

__attribute__((used)) static int
macio_release_resource(device_t bus, device_t child, int type, int rid,
		       struct resource *res)
{
	if (rman_get_flags(res) & RF_ACTIVE) {
		int error = bus_deactivate_resource(child, type, rid, res);
		if (error)
			return error;
	}

	return (rman_release_resource(res));
}