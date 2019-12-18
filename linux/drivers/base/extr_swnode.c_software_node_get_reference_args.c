#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct swnode {TYPE_1__* node; } ;
struct software_node_reference {int nrefs; TYPE_3__* refs; scalar_t__ name; } ;
struct TYPE_5__ {unsigned int u32_data; } ;
struct property_entry {TYPE_2__ value; } ;
struct fwnode_reference_args {unsigned int nargs; int /*<<< orphan*/ * args; int /*<<< orphan*/  fwnode; } ;
struct fwnode_handle {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * args; int /*<<< orphan*/  node; } ;
struct TYPE_4__ {int /*<<< orphan*/  properties; struct software_node_reference* references; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 unsigned int NR_FWNODE_REFERENCE_ARGS ; 
 struct property_entry* property_entry_get (int /*<<< orphan*/ ,char const*) ; 
 struct fwnode_handle* software_node_fwnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  software_node_get (struct fwnode_handle*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 
 struct swnode* to_swnode (struct fwnode_handle const*) ; 

__attribute__((used)) static int
software_node_get_reference_args(const struct fwnode_handle *fwnode,
				 const char *propname, const char *nargs_prop,
				 unsigned int nargs, unsigned int index,
				 struct fwnode_reference_args *args)
{
	struct swnode *swnode = to_swnode(fwnode);
	const struct software_node_reference *ref;
	const struct property_entry *prop;
	struct fwnode_handle *refnode;
	int i;

	if (!swnode || !swnode->node->references)
		return -ENOENT;

	for (ref = swnode->node->references; ref->name; ref++)
		if (!strcmp(ref->name, propname))
			break;

	if (!ref->name || index > (ref->nrefs - 1))
		return -ENOENT;

	refnode = software_node_fwnode(ref->refs[index].node);
	if (!refnode)
		return -ENOENT;

	if (nargs_prop) {
		prop = property_entry_get(swnode->node->properties, nargs_prop);
		if (!prop)
			return -EINVAL;

		nargs = prop->value.u32_data;
	}

	if (nargs > NR_FWNODE_REFERENCE_ARGS)
		return -EINVAL;

	args->fwnode = software_node_get(refnode);
	args->nargs = nargs;

	for (i = 0; i < nargs; i++)
		args->args[i] = ref->refs[index].args[i];

	return 0;
}