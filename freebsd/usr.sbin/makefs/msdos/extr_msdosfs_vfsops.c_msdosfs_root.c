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
struct vnode {struct denode* v_data; } ;
struct msdosfsmount {struct vnode* pm_devvp; } ;
struct denode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSDOSFSROOT ; 
 int /*<<< orphan*/  MSDOSFSROOT_OFS ; 
 int deget (struct msdosfsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct denode**) ; 
 int errno ; 

int
msdosfs_root(struct msdosfsmount *pmp, struct vnode *vp) {
	struct denode *ndep;
	int error;

	*vp = *pmp->pm_devvp;
	if ((error = deget(pmp, MSDOSFSROOT, MSDOSFSROOT_OFS, &ndep)) != 0) {
		errno = error;
		return -1;
	}
	vp->v_data = ndep;
	return 0;
}