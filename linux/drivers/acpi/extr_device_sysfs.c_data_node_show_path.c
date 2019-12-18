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
struct acpi_data_node {scalar_t__ handle; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_object_path (scalar_t__,char*) ; 

__attribute__((used)) static ssize_t data_node_show_path(struct acpi_data_node *dn, char *buf)
{
	return dn->handle ? acpi_object_path(dn->handle, buf) : 0;
}