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
struct kobject {int dummy; } ;
struct attribute {int dummy; } ;
struct acpi_data_node_attr {int /*<<< orphan*/  (* show ) (struct acpi_data_node*,char*) ;} ;
struct acpi_data_node {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  stub1 (struct acpi_data_node*,char*) ; 
 struct acpi_data_node_attr* to_attr (struct attribute*) ; 
 struct acpi_data_node* to_data_node (struct kobject*) ; 

__attribute__((used)) static ssize_t acpi_data_node_attr_show(struct kobject *kobj,
					struct attribute *attr, char *buf)
{
	struct acpi_data_node *dn = to_data_node(kobj);
	struct acpi_data_node_attr *dn_attr = to_attr(attr);

	return dn_attr->show ? dn_attr->show(dn, buf) : -ENXIO;
}