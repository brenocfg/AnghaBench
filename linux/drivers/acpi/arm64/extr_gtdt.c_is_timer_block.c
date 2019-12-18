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
struct acpi_gtdt_header {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ACPI_GTDT_TYPE_TIMER_BLOCK ; 

__attribute__((used)) static inline bool is_timer_block(void *platform_timer)
{
	struct acpi_gtdt_header *gh = platform_timer;

	return gh->type == ACPI_GTDT_TYPE_TIMER_BLOCK;
}