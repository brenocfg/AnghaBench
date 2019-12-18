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
struct vnode {int dummy; } ;
struct unionfs_node_hashhead {int dummy; } ;
struct unionfs_node {char un_hashmask; struct unionfs_node_hashhead* un_hashtbl; } ;

/* Variables and functions */
 struct unionfs_node* VTOUNIONFS (struct vnode*) ; 

__attribute__((used)) static struct unionfs_node_hashhead *
unionfs_get_hashhead(struct vnode *dvp, char *path)
{
	int		count;
	char		hash;
	struct unionfs_node *unp;

	hash = 0;
	unp = VTOUNIONFS(dvp);
	if (path != NULL) {
		for (count = 0; path[count]; count++)
			hash += path[count];
	}

	return (&(unp->un_hashtbl[hash & (unp->un_hashmask)]));
}