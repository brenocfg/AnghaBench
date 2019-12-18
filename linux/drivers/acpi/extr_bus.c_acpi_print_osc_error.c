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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int length; scalar_t__ pointer; } ;
struct acpi_osc_context {TYPE_1__ cap; int /*<<< orphan*/  uuid_str; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_handle_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static void acpi_print_osc_error(acpi_handle handle,
				 struct acpi_osc_context *context, char *error)
{
	int i;

	acpi_handle_debug(handle, "(%s): %s\n", context->uuid_str, error);

	pr_debug("_OSC request data:");
	for (i = 0; i < context->cap.length; i += sizeof(u32))
		pr_debug(" %x", *((u32 *)(context->cap.pointer + i)));

	pr_debug("\n");
}