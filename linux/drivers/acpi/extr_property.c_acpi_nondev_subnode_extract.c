#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* elements; } ;
union acpi_object {TYPE_3__ package; } ;
struct list_head {int dummy; } ;
struct fwnode_handle {int dummy; } ;
struct TYPE_10__ {union acpi_object const* pointer; int /*<<< orphan*/  subnodes; int /*<<< orphan*/  properties; } ;
struct TYPE_11__ {int /*<<< orphan*/ * ops; } ;
struct acpi_data_node {int /*<<< orphan*/  sibling; TYPE_4__ data; int /*<<< orphan*/ * handle; TYPE_6__ fwnode; struct fwnode_handle* parent; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/ * acpi_handle ;
struct TYPE_7__ {int /*<<< orphan*/  pointer; } ;
struct TYPE_8__ {TYPE_1__ string; } ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_data_fwnode_ops ; 
 scalar_t__ acpi_enumerate_nondev_subnodes (int /*<<< orphan*/ *,union acpi_object const*,TYPE_4__*,TYPE_6__*) ; 
 int acpi_extract_properties (union acpi_object const*,TYPE_4__*) ; 
 int /*<<< orphan*/  acpi_get_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  acpi_handle_debug (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct acpi_data_node*) ; 
 struct acpi_data_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static bool acpi_nondev_subnode_extract(const union acpi_object *desc,
					acpi_handle handle,
					const union acpi_object *link,
					struct list_head *list,
					struct fwnode_handle *parent)
{
	struct acpi_data_node *dn;
	bool result;

	dn = kzalloc(sizeof(*dn), GFP_KERNEL);
	if (!dn)
		return false;

	dn->name = link->package.elements[0].string.pointer;
	dn->fwnode.ops = &acpi_data_fwnode_ops;
	dn->parent = parent;
	INIT_LIST_HEAD(&dn->data.properties);
	INIT_LIST_HEAD(&dn->data.subnodes);

	result = acpi_extract_properties(desc, &dn->data);

	if (handle) {
		acpi_handle scope;
		acpi_status status;

		/*
		 * The scope for the subnode object lookup is the one of the
		 * namespace node (device) containing the object that has
		 * returned the package.  That is, it's the scope of that
		 * object's parent.
		 */
		status = acpi_get_parent(handle, &scope);
		if (ACPI_SUCCESS(status)
		    && acpi_enumerate_nondev_subnodes(scope, desc, &dn->data,
						      &dn->fwnode))
			result = true;
	} else if (acpi_enumerate_nondev_subnodes(NULL, desc, &dn->data,
						  &dn->fwnode)) {
		result = true;
	}

	if (result) {
		dn->handle = handle;
		dn->data.pointer = desc;
		list_add_tail(&dn->sibling, list);
		return true;
	}

	kfree(dn);
	acpi_handle_debug(handle, "Invalid properties/subnodes data, skipping\n");
	return false;
}