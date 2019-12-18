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
struct xrcd_table_entry {int /*<<< orphan*/  node; } ;
struct inode {int dummy; } ;
struct ib_uverbs_device {int /*<<< orphan*/  xrcd_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct xrcd_table_entry*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct xrcd_table_entry* xrcd_table_search (struct ib_uverbs_device*,struct inode*) ; 

__attribute__((used)) static void xrcd_table_delete(struct ib_uverbs_device *dev,
			      struct inode *inode)
{
	struct xrcd_table_entry *entry;

	entry = xrcd_table_search(dev, inode);
	if (entry) {
		iput(inode);
		rb_erase(&entry->node, &dev->xrcd_tree);
		kfree(entry);
	}
}