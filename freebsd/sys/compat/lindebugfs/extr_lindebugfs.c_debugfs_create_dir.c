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
struct pfs_node {struct dentry_meta* pn_data; } ;
struct dentry {struct pfs_node* d_pfs_node; } ;
struct dentry_meta {int dm_mode; int /*<<< orphan*/  dm_type; struct dentry dm_dnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_DIR ; 
 int /*<<< orphan*/  M_DFSINT ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int PFS_NOWAIT ; 
 int PFS_RD ; 
 int /*<<< orphan*/  debugfs_attr ; 
 int /*<<< orphan*/  debugfs_destroy ; 
 struct pfs_node* debugfs_root ; 
 int /*<<< orphan*/  free (struct dentry_meta*,int /*<<< orphan*/ ) ; 
 struct dentry_meta* malloc (int,int /*<<< orphan*/ ,int) ; 
 struct pfs_node* pfs_create_dir (struct pfs_node*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

struct dentry *
debugfs_create_dir(const char *name, struct dentry *parent)
{
	struct dentry_meta *dm;
	struct dentry *dnode;
	struct pfs_node *pnode;

	dm = malloc(sizeof(*dm), M_DFSINT, M_NOWAIT | M_ZERO);
	if (dm == NULL)
		return (NULL);
	dnode = &dm->dm_dnode;
	dm->dm_mode = 0700;
	dm->dm_type = DM_DIR;
	if (parent != NULL)
		pnode = parent->d_pfs_node;
	else
		pnode = debugfs_root;

	dnode->d_pfs_node = pfs_create_dir(pnode, name, debugfs_attr, NULL, debugfs_destroy, PFS_RD | PFS_NOWAIT);
	if (dnode->d_pfs_node == NULL) {
		free(dm, M_DFSINT);
		return (NULL);
	}
	dnode->d_pfs_node->pn_data = dm;
	return (dnode);
}