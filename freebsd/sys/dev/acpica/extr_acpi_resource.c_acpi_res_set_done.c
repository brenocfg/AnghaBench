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
struct acpi_res_context {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiOsFree (struct acpi_res_context*) ; 

__attribute__((used)) static void
acpi_res_set_done(device_t dev, void *context)
{
    struct acpi_res_context	*cp = (struct acpi_res_context *)context;

    if (cp == NULL)
	return;
    AcpiOsFree(cp);
}