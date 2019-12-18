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
struct resource_map {int dummy; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int RF_UNMAPPED ; 
 int SYS_RES_IOPORT ; 
 int SYS_RES_MEMORY ; 
 int nexus_map_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*,int /*<<< orphan*/ *,struct resource_map*) ; 
 int rman_activate_resource (struct resource*) ; 
 int /*<<< orphan*/  rman_deactivate_resource (struct resource*) ; 
 int rman_get_flags (struct resource*) ; 
 int /*<<< orphan*/  rman_set_mapping (struct resource*,struct resource_map*) ; 

__attribute__((used)) static int
nexus_activate_resource(device_t bus, device_t child, int type, int rid,
			struct resource *r)
{
	struct resource_map map;
	int error;

	error = rman_activate_resource(r);
	if (error != 0)
		return (error);

	if (!(rman_get_flags(r) & RF_UNMAPPED) &&
	    (type == SYS_RES_MEMORY || type == SYS_RES_IOPORT)) {
		error = nexus_map_resource(bus, child, type, r, NULL, &map);
		if (error) {
			rman_deactivate_resource(r);
			return (error);
		}

		rman_set_mapping(r,&map);
	}
	return (0);
}