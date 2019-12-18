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
 scalar_t__ acpi_is_resource_managed (int,struct resource*) ; 
 int bus_deactivate_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int bus_generic_rl_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int rman_get_flags (struct resource*) ; 
 int rman_release_resource (struct resource*) ; 

__attribute__((used)) static int
acpi_release_resource(device_t bus, device_t child, int type, int rid,
    struct resource *r)
{
    int ret;

    /*
     * If this resource belongs to one of our internal managers,
     * deactivate it and release it to the local pool.
     */
    if (acpi_is_resource_managed(type, r)) {
	if (rman_get_flags(r) & RF_ACTIVE) {
	    ret = bus_deactivate_resource(child, type, rid, r);
	    if (ret != 0)
		return (ret);
	}
	return (rman_release_resource(r));
    }

    return (bus_generic_rl_release_resource(bus, child, type, rid, r));
}