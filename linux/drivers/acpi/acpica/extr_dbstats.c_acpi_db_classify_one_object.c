#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union acpi_parse_object {int dummy; } acpi_parse_object ;
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;
typedef  size_t u32 ;
struct acpi_namespace_node {size_t type; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_handle ;
struct TYPE_4__ {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 size_t ACPI_TYPE_NS_NODE_MAX ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_db_enumerate_object (union acpi_operand_object*) ; 
 int /*<<< orphan*/ * acpi_gbl_node_type_count ; 
 int /*<<< orphan*/  acpi_gbl_node_type_count_misc ; 
 int /*<<< orphan*/  acpi_gbl_num_nodes ; 
 union acpi_operand_object* acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 TYPE_1__* acpi_ps_get_depth_next (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ acpi_ps_is_named_op (int /*<<< orphan*/ ) ; 
 scalar_t__ is_method ; 
 size_t num_grammar_elements ; 
 size_t num_method_elements ; 
 size_t num_nodes ; 
 TYPE_1__* op ; 
 int /*<<< orphan*/  root ; 
 size_t size_of_acpi_objects ; 
 size_t size_of_method_trees ; 
 size_t size_of_node_entries ; 
 size_t size_of_parse_tree ; 

__attribute__((used)) static acpi_status
acpi_db_classify_one_object(acpi_handle obj_handle,
			    u32 nesting_level,
			    void *context, void **return_value)
{
	struct acpi_namespace_node *node;
	union acpi_operand_object *obj_desc;
	u32 type;

	acpi_gbl_num_nodes++;

	node = (struct acpi_namespace_node *)obj_handle;
	obj_desc = acpi_ns_get_attached_object(node);

	acpi_db_enumerate_object(obj_desc);

	type = node->type;
	if (type > ACPI_TYPE_NS_NODE_MAX) {
		acpi_gbl_node_type_count_misc++;
	} else {
		acpi_gbl_node_type_count[type]++;
	}

	return (AE_OK);

#ifdef ACPI_FUTURE_IMPLEMENTATION

	/* TBD: These need to be counted during the initial parsing phase */

	if (acpi_ps_is_named_op(op->opcode)) {
		num_nodes++;
	}

	if (is_method) {
		num_method_elements++;
	}

	num_grammar_elements++;
	op = acpi_ps_get_depth_next(root, op);

	size_of_parse_tree = (num_grammar_elements - num_method_elements) *
	    (u32)sizeof(union acpi_parse_object);
	size_of_method_trees =
	    num_method_elements * (u32)sizeof(union acpi_parse_object);
	size_of_node_entries =
	    num_nodes * (u32)sizeof(struct acpi_namespace_node);
	size_of_acpi_objects =
	    num_nodes * (u32)sizeof(union acpi_operand_object);
#endif
}