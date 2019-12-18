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
typedef  int uint64_t ;
struct vnode {int dummy; } ;
struct denode {int de_Attributes; int de_dirclust; scalar_t__ de_inode; scalar_t__ de_diroffset; TYPE_1__* de_pmp; } ;
struct TYPE_2__ {scalar_t__ pm_bpcluster; } ;

/* Variables and functions */
 int ATTR_DIRECTORY ; 
 struct vnode* DETOV (struct denode*) ; 
 int /*<<< orphan*/  vfs_hash_rehash (struct vnode*,scalar_t__) ; 

void
reinsert(struct denode *dep)
{
	struct vnode *vp;

	/*
	 * Fix up the denode cache.  If the denode is for a directory,
	 * there is nothing to do since the hash is based on the starting
	 * cluster of the directory file and that hasn't changed.  If for a
	 * file the hash is based on the location of the directory entry,
	 * so we must remove it from the cache and re-enter it with the
	 * hash based on the new location of the directory entry.
	 */
#if 0
	if (dep->de_Attributes & ATTR_DIRECTORY)
		return;
#endif
	vp = DETOV(dep);
	dep->de_inode = (uint64_t)dep->de_pmp->pm_bpcluster * dep->de_dirclust +
	    dep->de_diroffset;
	vfs_hash_rehash(vp, dep->de_inode);
}