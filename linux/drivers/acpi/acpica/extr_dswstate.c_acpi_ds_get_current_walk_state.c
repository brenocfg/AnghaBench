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
struct acpi_walk_state {int dummy; } ;
struct acpi_thread_state {struct acpi_walk_state* walk_state_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_PARSE ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds_get_current_walk_state ; 

struct acpi_walk_state *acpi_ds_get_current_walk_state(struct acpi_thread_state
						       *thread)
{
	ACPI_FUNCTION_NAME(ds_get_current_walk_state);

	if (!thread) {
		return (NULL);
	}

	ACPI_DEBUG_PRINT((ACPI_DB_PARSE, "Current WalkState %p\n",
			  thread->walk_state_list));

	return (thread->walk_state_list);
}