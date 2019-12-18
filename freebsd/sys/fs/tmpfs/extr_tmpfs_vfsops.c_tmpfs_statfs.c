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
struct tmpfs_mount {scalar_t__ tm_pages_max; size_t tm_nodes_inuse; size_t tm_nodes_max; } ;
struct statfs {scalar_t__ f_blocks; size_t f_bavail; size_t f_bfree; size_t f_files; size_t f_ffree; void* f_bsize; void* f_iosize; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 void* PAGE_SIZE ; 
 scalar_t__ ULONG_MAX ; 
 struct tmpfs_mount* VFS_TO_TMPFS (struct mount*) ; 
 scalar_t__ tmpfs_mem_avail () ; 
 size_t tmpfs_pages_used (struct tmpfs_mount*) ; 

__attribute__((used)) static int
tmpfs_statfs(struct mount *mp, struct statfs *sbp)
{
	struct tmpfs_mount *tmp;
	size_t used;

	tmp = VFS_TO_TMPFS(mp);

	sbp->f_iosize = PAGE_SIZE;
	sbp->f_bsize = PAGE_SIZE;

	used = tmpfs_pages_used(tmp);
	if (tmp->tm_pages_max != ULONG_MAX)
		 sbp->f_blocks = tmp->tm_pages_max;
	else
		 sbp->f_blocks = used + tmpfs_mem_avail();
	if (sbp->f_blocks <= used)
		sbp->f_bavail = 0;
	else
		sbp->f_bavail = sbp->f_blocks - used;
	sbp->f_bfree = sbp->f_bavail;
	used = tmp->tm_nodes_inuse;
	sbp->f_files = tmp->tm_nodes_max;
	if (sbp->f_files <= used)
		sbp->f_ffree = 0;
	else
		sbp->f_ffree = sbp->f_files - used;
	/* sbp->f_owner = tmp->tn_uid; */

	return 0;
}