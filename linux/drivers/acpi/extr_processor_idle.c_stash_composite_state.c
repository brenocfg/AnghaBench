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
struct acpi_lpi_states_array {int /*<<< orphan*/  composite_states_size; struct acpi_lpi_state** composite_states; } ;
struct acpi_lpi_state {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void stash_composite_state(struct acpi_lpi_states_array *curr_level,
				  struct acpi_lpi_state *t)
{
	curr_level->composite_states[curr_level->composite_states_size++] = t;
}