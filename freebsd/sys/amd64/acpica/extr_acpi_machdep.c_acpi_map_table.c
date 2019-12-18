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
typedef  int /*<<< orphan*/  vm_paddr_t ;

/* Variables and functions */
 void* map_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

void *
acpi_map_table(vm_paddr_t pa, const char *sig)
{

	return (map_table(pa, 0, sig));
}