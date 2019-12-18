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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_iort_node {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int IORT_TYPE_MASK (int /*<<< orphan*/ ) ; 
 struct acpi_iort_node* iort_node_get_id (struct acpi_iort_node*,int /*<<< orphan*/ *,int) ; 
 struct acpi_iort_node* iort_node_map_id (struct acpi_iort_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct acpi_iort_node *iort_node_map_platform_id(
		struct acpi_iort_node *node, u32 *id_out, u8 type_mask,
		int index)
{
	struct acpi_iort_node *parent;
	u32 id;

	/* step 1: retrieve the initial dev id */
	parent = iort_node_get_id(node, &id, index);
	if (!parent)
		return NULL;

	/*
	 * optional step 2: map the initial dev id if its parent is not
	 * the target type we want, map it again for the use cases such
	 * as NC (named component) -> SMMU -> ITS. If the type is matched,
	 * return the initial dev id and its parent pointer directly.
	 */
	if (!(IORT_TYPE_MASK(parent->type) & type_mask))
		parent = iort_node_map_id(parent, id, id_out, type_mask);
	else
		if (id_out)
			*id_out = id;

	return parent;
}