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
struct inode {int i_flag; int /*<<< orphan*/  i_ea_refs; } ;

/* Variables and functions */
 int IN_EA_LOCKED ; 
 int IN_EA_LOCKWAIT ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 struct inode* VTOI (struct vnode*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ffs_unlock_ea(struct vnode *vp)
{
	struct inode *ip;

	ip = VTOI(vp);
	VI_LOCK(vp);
	if (ip->i_flag & IN_EA_LOCKWAIT)
		wakeup(&ip->i_ea_refs);
	ip->i_flag &= ~(IN_EA_LOCKED | IN_EA_LOCKWAIT);
	VI_UNLOCK(vp);
}