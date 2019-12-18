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
struct dentry {int /*<<< orphan*/  d_pfs_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  pfs_destroy (int /*<<< orphan*/ ) ; 

void
debugfs_remove_recursive(struct dentry *dnode)
{
	if (dnode == NULL)
		return;

	pfs_destroy(dnode->d_pfs_node);
}