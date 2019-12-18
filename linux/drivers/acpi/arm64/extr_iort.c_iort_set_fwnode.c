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
struct iort_fwnode {int /*<<< orphan*/  list; struct fwnode_handle* fwnode; struct acpi_iort_node* iort_node; } ;
struct fwnode_handle {int dummy; } ;
struct acpi_iort_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  iort_fwnode_list ; 
 int /*<<< orphan*/  iort_fwnode_lock ; 
 struct iort_fwnode* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int iort_set_fwnode(struct acpi_iort_node *iort_node,
				  struct fwnode_handle *fwnode)
{
	struct iort_fwnode *np;

	np = kzalloc(sizeof(struct iort_fwnode), GFP_ATOMIC);

	if (WARN_ON(!np))
		return -ENOMEM;

	INIT_LIST_HEAD(&np->list);
	np->iort_node = iort_node;
	np->fwnode = fwnode;

	spin_lock(&iort_fwnode_lock);
	list_add_tail(&np->list, &iort_fwnode_list);
	spin_unlock(&iort_fwnode_lock);

	return 0;
}