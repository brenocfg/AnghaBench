#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ucred {int /*<<< orphan*/  cr_gid; int /*<<< orphan*/  cr_uid; TYPE_1__* cr_prison; } ;
struct mqfs_node {int mn_type; int mn_refcount; int mn_mode; int /*<<< orphan*/  mn_gid; int /*<<< orphan*/  mn_uid; int /*<<< orphan*/  mn_birth; int /*<<< orphan*/  mn_mtime; int /*<<< orphan*/  mn_atime; int /*<<< orphan*/  mn_ctime; int /*<<< orphan*/  mn_pr_root; int /*<<< orphan*/  mn_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  pr_root; } ;

/* Variables and functions */
 struct mqfs_node* mqnode_alloc () ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  vfs_timestamp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mqfs_node *
mqfs_create_node(const char *name, int namelen, struct ucred *cred, int mode,
	int nodetype)
{
	struct mqfs_node *node;

	node = mqnode_alloc();
	strncpy(node->mn_name, name, namelen);
	node->mn_pr_root = cred->cr_prison->pr_root;
	node->mn_type = nodetype;
	node->mn_refcount = 1;
	vfs_timestamp(&node->mn_birth);
	node->mn_ctime = node->mn_atime = node->mn_mtime
		= node->mn_birth;
	node->mn_uid = cred->cr_uid;
	node->mn_gid = cred->cr_gid;
	node->mn_mode = mode;
	return (node);
}