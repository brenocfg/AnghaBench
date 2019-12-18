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
struct vnode {int /*<<< orphan*/  v_interlock; } ;
struct inode {int i_flag; int /*<<< orphan*/  i_ea_refs; } ;

/* Variables and functions */
 int IN_EA_LOCKED ; 
 int IN_EA_LOCKWAIT ; 
 scalar_t__ PINOD ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 struct inode* VTOI (struct vnode*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ffs_lock_ea(struct vnode *vp)
{
	struct inode *ip;

	ip = VTOI(vp);
	VI_LOCK(vp);
	while (ip->i_flag & IN_EA_LOCKED) {
		ip->i_flag |= IN_EA_LOCKWAIT;
		msleep(&ip->i_ea_refs, &vp->v_interlock, PINOD + 2, "ufs_ea",
		    0);
	}
	ip->i_flag |= IN_EA_LOCKED;
	VI_UNLOCK(vp);
}