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
typedef  int /*<<< orphan*/  uint64_t ;
struct acpi_res_context {int /*<<< orphan*/  ar_nio; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_res_set_ioport(device_t dev, void *context, uint64_t base,
		    uint64_t length)
{
    struct acpi_res_context	*cp = (struct acpi_res_context *)context;

    if (cp == NULL)
	return;
    bus_set_resource(dev, SYS_RES_IOPORT, cp->ar_nio++, base, length);
}