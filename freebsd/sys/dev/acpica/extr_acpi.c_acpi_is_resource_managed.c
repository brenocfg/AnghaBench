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

/* Variables and functions */
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  acpi_rman_io ; 
 int /*<<< orphan*/  acpi_rman_mem ; 
 int rman_is_region_manager (struct resource*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
acpi_is_resource_managed(int type, struct resource *r)
{

    /* We only handle memory and IO resources through rman. */
    switch (type) {
    case SYS_RES_IOPORT:
	return (rman_is_region_manager(r, &acpi_rman_io));
    case SYS_RES_MEMORY:
	return (rman_is_region_manager(r, &acpi_rman_mem));
    }
    return (0);
}