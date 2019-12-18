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
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ acpi_is_resource_managed (int,struct resource*) ; 
 int bus_generic_adjust_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rman_adjust_resource (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_adjust_resource(device_t bus, device_t child, int type, struct resource *r,
    rman_res_t start, rman_res_t end)
{

    if (acpi_is_resource_managed(type, r))
	return (rman_adjust_resource(r, start, end));
    return (bus_generic_adjust_resource(bus, child, type, r, start, end));
}