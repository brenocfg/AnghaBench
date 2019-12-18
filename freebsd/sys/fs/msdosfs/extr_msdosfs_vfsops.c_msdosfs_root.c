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
struct msdosfsmount {int dummy; } ;
struct mount {int dummy; } ;
struct denode {int dummy; } ;

/* Variables and functions */
 struct vnode* DETOV (struct denode*) ; 
 int /*<<< orphan*/  MSDOSFSROOT ; 
 int /*<<< orphan*/  MSDOSFSROOT_OFS ; 
 struct msdosfsmount* VFSTOMSDOSFS (struct mount*) ; 
 int deget (struct msdosfsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct denode**) ; 
 int /*<<< orphan*/  printf (char*,struct mount*,struct msdosfsmount*) ; 

__attribute__((used)) static int
msdosfs_root(struct mount *mp, int flags, struct vnode **vpp)
{
	struct msdosfsmount *pmp = VFSTOMSDOSFS(mp);
	struct denode *ndep;
	int error;

#ifdef MSDOSFS_DEBUG
	printf("msdosfs_root(); mp %p, pmp %p\n", mp, pmp);
#endif
	error = deget(pmp, MSDOSFSROOT, MSDOSFSROOT_OFS, &ndep);
	if (error)
		return (error);
	*vpp = DETOV(ndep);
	return (0);
}