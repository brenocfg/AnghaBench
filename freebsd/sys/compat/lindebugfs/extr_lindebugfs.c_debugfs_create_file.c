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
typedef  int /*<<< orphan*/  umode_t ;
struct pfs_node {struct dentry_meta* pn_data; } ;
struct file_operations {scalar_t__ write; } ;
struct dentry {struct pfs_node* d_pfs_node; } ;
struct dentry_meta {int /*<<< orphan*/  dm_type; int /*<<< orphan*/  dm_mode; void* dm_data; struct file_operations const* dm_fops; struct dentry dm_dnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_FILE ; 
 int /*<<< orphan*/  M_DFSINT ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int PFS_NOWAIT ; 
 int PFS_RD ; 
 int PFS_RDWR ; 
 int /*<<< orphan*/  debugfs_attr ; 
 int /*<<< orphan*/  debugfs_destroy ; 
 int /*<<< orphan*/  debugfs_fill ; 
 struct pfs_node* debugfs_root ; 
 int /*<<< orphan*/  free (struct dentry_meta*,int /*<<< orphan*/ ) ; 
 struct dentry_meta* malloc (int,int /*<<< orphan*/ ,int) ; 
 struct pfs_node* pfs_create_file (struct pfs_node*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

struct dentry *
debugfs_create_file(const char *name, umode_t mode,
		    struct dentry *parent, void *data,
		    const struct file_operations *fops)
{
	struct dentry_meta *dm;
	struct dentry *dnode;
	struct pfs_node *pnode;
	int flags;

	dm = malloc(sizeof(*dm), M_DFSINT, M_NOWAIT | M_ZERO);
	if (dm == NULL)
		return (NULL);
	dnode = &dm->dm_dnode;
	dm->dm_fops = fops;
	dm->dm_data = data;
	dm->dm_mode = mode;
	dm->dm_type = DM_FILE;
	if (parent != NULL)
		pnode = parent->d_pfs_node;
	else
		pnode = debugfs_root;

	flags = fops->write ? PFS_RDWR : PFS_RD;
	dnode->d_pfs_node = pfs_create_file(pnode, name, debugfs_fill,
	    debugfs_attr, NULL, debugfs_destroy, flags | PFS_NOWAIT);
	if (dnode->d_pfs_node == NULL) {
		free(dm, M_DFSINT);
		return (NULL);
	}
	dnode->d_pfs_node->pn_data = dm;

	return (dnode);
}