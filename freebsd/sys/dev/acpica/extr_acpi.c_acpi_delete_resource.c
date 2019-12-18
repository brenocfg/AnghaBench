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
struct resource_list {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct resource_list* acpi_get_rlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ resource_list_busy (struct resource_list*,int,int) ; 
 int /*<<< orphan*/  resource_list_delete (struct resource_list*,int,int) ; 
 int /*<<< orphan*/  resource_list_unreserve (struct resource_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
acpi_delete_resource(device_t bus, device_t child, int type, int rid)
{
    struct resource_list *rl;

    rl = acpi_get_rlist(bus, child);
    if (resource_list_busy(rl, type, rid)) {
	device_printf(bus, "delete_resource: Resource still owned by child"
	    " (type=%d, rid=%d)\n", type, rid);
	return;
    }
    resource_list_unreserve(rl, bus, child, type, rid);
    resource_list_delete(rl, type, rid);
}