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
struct resource_list_entry {int /*<<< orphan*/  count; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct resource {int dummy; } ;
struct gic_v3_ofw_devinfo {int /*<<< orphan*/  di_rl; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int OF_getproplen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RMAN_IS_DEFAULT_RANGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 struct resource* bus_generic_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gic_v3_ofw_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_has_prop (int /*<<< orphan*/ ,char*) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static struct resource *
gic_v3_ofw_bus_alloc_res(device_t bus, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct gic_v3_ofw_devinfo *di;
	struct resource_list_entry *rle;
	int ranges_len;

	if (RMAN_IS_DEFAULT_RANGE(start, end)) {
		if ((di = device_get_ivars(child)) == NULL)
			return (NULL);
		if (type != SYS_RES_MEMORY)
			return (NULL);

		/* Find defaults for this rid */
		rle = resource_list_find(&di->di_rl, type, *rid);
		if (rle == NULL)
			return (NULL);

		start = rle->start;
		end = rle->end;
		count = rle->count;
	}
	/*
	 * XXX: No ranges remap!
	 *	Absolute address is expected.
	 */
	if (ofw_bus_has_prop(bus, "ranges")) {
		ranges_len = OF_getproplen(ofw_bus_get_node(bus), "ranges");
		if (ranges_len != 0) {
			if (bootverbose) {
				device_printf(child,
				    "Ranges remap not supported\n");
			}
			return (NULL);
		}
	}
	return (bus_generic_alloc_resource(bus, child, type, rid, start, end,
	    count, flags));
}