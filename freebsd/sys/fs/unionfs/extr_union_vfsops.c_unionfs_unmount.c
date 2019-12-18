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
struct unionfs_mount {int dummy; } ;
struct mount {int mnt_nvnodelistsize; int /*<<< orphan*/ * mnt_data; } ;

/* Variables and functions */
 int FORCECLOSE ; 
 int MNT_FORCE ; 
 struct unionfs_mount* MOUNTTOUNIONFSMOUNT (struct mount*) ; 
 int /*<<< orphan*/  M_UNIONFSMNT ; 
 int /*<<< orphan*/  UNIONFSDEBUG (char*,void*) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  free (struct unionfs_mount*,int /*<<< orphan*/ ) ; 
 int vflush (struct mount*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
unionfs_unmount(struct mount *mp, int mntflags)
{
	struct unionfs_mount *ump;
	int		error;
	int		num;
	int		freeing;
	int		flags;

	UNIONFSDEBUG("unionfs_unmount: mp = %p\n", (void *)mp);

	ump = MOUNTTOUNIONFSMOUNT(mp);
	flags = 0;

	if (mntflags & MNT_FORCE)
		flags |= FORCECLOSE;

	/* vflush (no need to call vrele) */
	for (freeing = 0; (error = vflush(mp, 1, flags, curthread)) != 0;) {
		num = mp->mnt_nvnodelistsize;
		if (num == freeing)
			break;
		freeing = num;
	}

	if (error)
		return (error);

	free(ump, M_UNIONFSMNT);
	mp->mnt_data = NULL;

	return (0);
}