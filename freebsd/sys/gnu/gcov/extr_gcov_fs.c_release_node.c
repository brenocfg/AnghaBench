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
struct gcov_node {scalar_t__ unloaded_info; struct gcov_node* loaded_info; int /*<<< orphan*/  dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct gcov_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_GCOV ; 
 int /*<<< orphan*/  all_entry ; 
 int /*<<< orphan*/  children_entry ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct gcov_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcov_info_free (scalar_t__) ; 
 int /*<<< orphan*/  remove_links (struct gcov_node*) ; 

__attribute__((used)) static void
release_node(struct gcov_node *node)
{
	LIST_REMOVE(node, children_entry);
	LIST_REMOVE(node, all_entry);
	debugfs_remove(node->dentry);
	remove_links(node);
	free(node->loaded_info, M_GCOV);
	if (node->unloaded_info)
		gcov_info_free(node->unloaded_info);
	free(node, M_GCOV);
}