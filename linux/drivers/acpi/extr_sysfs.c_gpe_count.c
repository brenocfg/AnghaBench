#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 size_t ACPI_NUM_FIXED_EVENTS ; 
 size_t COUNT_ERROR ; 
 int /*<<< orphan*/  acpi_gpe_count ; 
 TYPE_1__* all_counters ; 
 size_t num_gpes ; 

__attribute__((used)) static void gpe_count(u32 gpe_number)
{
	acpi_gpe_count++;

	if (!all_counters)
		return;

	if (gpe_number < num_gpes)
		all_counters[gpe_number].count++;
	else
		all_counters[num_gpes + ACPI_NUM_FIXED_EVENTS +
			     COUNT_ERROR].count++;

	return;
}