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
struct mqfs_node {char* mn_name; int mn_refcount; int /*<<< orphan*/  mn_type; } ;

/* Variables and functions */
 scalar_t__ mqfs_add_node (struct mqfs_node*,struct mqfs_node*) ; 
 int /*<<< orphan*/  mqfstype_parent ; 
 int /*<<< orphan*/  mqfstype_this ; 
 struct mqfs_node* mqnode_alloc () ; 
 int /*<<< orphan*/  mqnode_free (struct mqfs_node*) ; 

__attribute__((used)) static int
mqfs_fixup_dir(struct mqfs_node *parent)
{
	struct mqfs_node *dir;

	dir = mqnode_alloc();
	dir->mn_name[0] = '.';
	dir->mn_type = mqfstype_this;
	dir->mn_refcount = 1;
	if (mqfs_add_node(parent, dir) != 0) {
		mqnode_free(dir);
		return (-1);
	}

	dir = mqnode_alloc();
	dir->mn_name[0] = dir->mn_name[1] = '.';
	dir->mn_type = mqfstype_parent;
	dir->mn_refcount = 1;

	if (mqfs_add_node(parent, dir) != 0) {
		mqnode_free(dir);
		return (-1);
	}

	return (0);
}