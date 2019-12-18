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
struct mount {int /*<<< orphan*/  mnt_listmtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRI_USER ; 
 int /*<<< orphan*/  kern_yield (int /*<<< orphan*/ ) ; 
 struct vnode* mnt_vnode_next_active (struct vnode**,struct mount*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ should_yield () ; 

struct vnode *
__mnt_vnode_next_active(struct vnode **mvp, struct mount *mp)
{

	if (should_yield())
		kern_yield(PRI_USER);
	mtx_lock(&mp->mnt_listmtx);
	return (mnt_vnode_next_active(mvp, mp));
}