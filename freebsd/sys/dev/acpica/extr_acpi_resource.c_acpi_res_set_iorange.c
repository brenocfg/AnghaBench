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
typedef  scalar_t__ uint64_t ;
struct acpi_res_context {int /*<<< orphan*/  ar_nio; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
acpi_res_set_iorange(device_t dev, void *context, uint64_t low,
		     uint64_t high, uint64_t length, uint64_t align)
{
    struct acpi_res_context	*cp = (struct acpi_res_context *)context;

    if (cp == NULL)
	return;

    /*
     * XXX: Some BIOSes contain buggy _CRS entries where fixed I/O
     * ranges have the maximum base address (_MAX) to the end of the
     * I/O range instead of the start.  These are then treated as a
     * relocatable I/O range rather than a fixed I/O resource.  As a
     * workaround, treat I/O resources encoded this way as fixed I/O
     * ports.
     */
    if (high == (low + length)) {
	if (bootverbose)
	    device_printf(dev,
		"_CRS has fixed I/O port range defined as relocatable\n");

	bus_set_resource(dev, SYS_RES_IOPORT, cp->ar_nio++, low, length);
	return;
    }

    device_printf(dev, "I/O range not supported\n");
}