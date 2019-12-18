#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fwnode_handle {int /*<<< orphan*/ * ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  kset; } ;
struct swnode {int id; unsigned int allocated; struct fwnode_handle fwnode; TYPE_1__ kobj; int /*<<< orphan*/  children; int /*<<< orphan*/  entry; int /*<<< orphan*/  child_ids; struct swnode* parent; struct software_node const* node; } ;
struct software_node {int name; int /*<<< orphan*/  properties; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct fwnode_handle* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct swnode*) ; 
 int kobject_init_and_add (TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  kobject_put (TYPE_1__*) ; 
 int /*<<< orphan*/  kobject_uevent (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct swnode* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  property_entries_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  software_node_ops ; 
 int /*<<< orphan*/  software_node_type ; 
 int /*<<< orphan*/  swnode_kset ; 
 int /*<<< orphan*/  swnode_root_ids ; 

__attribute__((used)) static struct fwnode_handle *
swnode_register(const struct software_node *node, struct swnode *parent,
		unsigned int allocated)
{
	struct swnode *swnode;
	int ret;

	swnode = kzalloc(sizeof(*swnode), GFP_KERNEL);
	if (!swnode) {
		ret = -ENOMEM;
		goto out_err;
	}

	ret = ida_simple_get(parent ? &parent->child_ids : &swnode_root_ids,
			     0, 0, GFP_KERNEL);
	if (ret < 0) {
		kfree(swnode);
		goto out_err;
	}

	swnode->id = ret;
	swnode->node = node;
	swnode->parent = parent;
	swnode->allocated = allocated;
	swnode->kobj.kset = swnode_kset;
	swnode->fwnode.ops = &software_node_ops;

	ida_init(&swnode->child_ids);
	INIT_LIST_HEAD(&swnode->entry);
	INIT_LIST_HEAD(&swnode->children);

	if (node->name)
		ret = kobject_init_and_add(&swnode->kobj, &software_node_type,
					   parent ? &parent->kobj : NULL,
					   "%s", node->name);
	else
		ret = kobject_init_and_add(&swnode->kobj, &software_node_type,
					   parent ? &parent->kobj : NULL,
					   "node%d", swnode->id);
	if (ret) {
		kobject_put(&swnode->kobj);
		return ERR_PTR(ret);
	}

	if (parent)
		list_add_tail(&swnode->entry, &parent->children);

	kobject_uevent(&swnode->kobj, KOBJ_ADD);
	return &swnode->fwnode;

out_err:
	if (allocated)
		property_entries_free(node->properties);
	return ERR_PTR(ret);
}