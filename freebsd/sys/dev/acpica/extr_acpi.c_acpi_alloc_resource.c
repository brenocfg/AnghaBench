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
struct resource_list_entry {int start; int end; int count; } ;
struct resource_list {int dummy; } ;
struct resource {int dummy; } ;
struct acpi_device {struct resource_list ad_rl; } ;
typedef  int rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_RESOURCE ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 struct resource* BUS_ALLOC_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int,int,int,int /*<<< orphan*/ ) ; 
 int RMAN_IS_DEFAULT_RANGE (int,int) ; 
 int SYS_RES_IRQ ; 
 struct resource* acpi_alloc_sysres (int /*<<< orphan*/ ,int,int*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_config_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_lookup_irq_resource (int /*<<< orphan*/ ,int,struct resource*,int /*<<< orphan*/ *) ; 
 struct acpi_device* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_list_add (struct resource_list*,int,int,int,int,int) ; 
 struct resource* resource_list_alloc (struct resource_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int,int,int,int /*<<< orphan*/ ) ; 
 struct resource_list_entry* resource_list_find (struct resource_list*,int,int) ; 

__attribute__((used)) static struct resource *
acpi_alloc_resource(device_t bus, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
#ifndef INTRNG
    ACPI_RESOURCE ares;
#endif
    struct acpi_device *ad;
    struct resource_list_entry *rle;
    struct resource_list *rl;
    struct resource *res;
    int isdefault = RMAN_IS_DEFAULT_RANGE(start, end);

    /*
     * First attempt at allocating the resource.  For direct children,
     * use resource_list_alloc() to handle reserved resources.  For
     * other devices, pass the request up to our parent.
     */
    if (bus == device_get_parent(child)) {
	ad = device_get_ivars(child);
	rl = &ad->ad_rl;

	/*
	 * Simulate the behavior of the ISA bus for direct children
	 * devices.  That is, if a non-default range is specified for
	 * a resource that doesn't exist, use bus_set_resource() to
	 * add the resource before allocating it.  Note that these
	 * resources will not be reserved.
	 */
	if (!isdefault && resource_list_find(rl, type, *rid) == NULL)
		resource_list_add(rl, type, *rid, start, end, count);
	res = resource_list_alloc(rl, bus, child, type, rid, start, end, count,
	    flags);
#ifndef INTRNG
	if (res != NULL && type == SYS_RES_IRQ) {
	    /*
	     * Since bus_config_intr() takes immediate effect, we cannot
	     * configure the interrupt associated with a device when we
	     * parse the resources but have to defer it until a driver
	     * actually allocates the interrupt via bus_alloc_resource().
	     *
	     * XXX: Should we handle the lookup failing?
	     */
	    if (ACPI_SUCCESS(acpi_lookup_irq_resource(child, *rid, res, &ares)))
		acpi_config_intr(child, &ares);
	}
#endif

	/*
	 * If this is an allocation of the "default" range for a given
	 * RID, fetch the exact bounds for this resource from the
	 * resource list entry to try to allocate the range from the
	 * system resource regions.
	 */
	if (res == NULL && isdefault) {
	    rle = resource_list_find(rl, type, *rid);
	    if (rle != NULL) {
		start = rle->start;
		end = rle->end;
		count = rle->count;
	    }
	}
    } else
	res = BUS_ALLOC_RESOURCE(device_get_parent(bus), child, type, rid,
	    start, end, count, flags);

    /*
     * If the first attempt failed and this is an allocation of a
     * specific range, try to satisfy the request via a suballocation
     * from our system resource regions.
     */
    if (res == NULL && start + count - 1 == end)
	res = acpi_alloc_sysres(child, type, rid, start, end, count, flags);
    return (res);
}