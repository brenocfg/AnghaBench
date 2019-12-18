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
struct acpi_namespace_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  FALSE ; 
 char* acpi_ns_get_normalized_pathname (struct acpi_namespace_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_get_external_pathname ; 
 int /*<<< orphan*/  return_PTR (char*) ; 

char *acpi_ns_get_external_pathname(struct acpi_namespace_node *node)
{
	char *name_buffer;

	ACPI_FUNCTION_TRACE_PTR(ns_get_external_pathname, node);

	name_buffer = acpi_ns_get_normalized_pathname(node, FALSE);
	return_PTR(name_buffer);
}