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
struct acpi_namespace_node {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  acpi_object_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  ns_get_type ; 
 int /*<<< orphan*/  return_UINT8 (int /*<<< orphan*/ ) ; 

acpi_object_type acpi_ns_get_type(struct acpi_namespace_node * node)
{
	ACPI_FUNCTION_TRACE(ns_get_type);

	if (!node) {
		ACPI_WARNING((AE_INFO, "Null Node parameter"));
		return_UINT8(ACPI_TYPE_ANY);
	}

	return_UINT8(node->type);
}