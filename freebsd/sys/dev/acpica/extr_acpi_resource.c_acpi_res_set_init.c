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
struct acpi_res_context {void* ar_parent; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct acpi_res_context* AcpiOsAllocate (int) ; 
 int /*<<< orphan*/  bzero (struct acpi_res_context*,int) ; 

__attribute__((used)) static void
acpi_res_set_init(device_t dev, void *arg, void **context)
{
    struct acpi_res_context	*cp;

    if ((cp = AcpiOsAllocate(sizeof(*cp))) != NULL) {
	bzero(cp, sizeof(*cp));
	cp->ar_parent = arg;
	*context = cp;
    }
}