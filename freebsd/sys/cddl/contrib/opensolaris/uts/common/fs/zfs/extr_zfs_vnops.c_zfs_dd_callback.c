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
struct mount {int dummy; } ;

/* Variables and functions */
 int vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
zfs_dd_callback(struct mount *mp, void *arg, int lkflags, struct vnode **vpp)
{
	int error;

	*vpp = arg;
	error = vn_lock(*vpp, lkflags);
	if (error != 0)
		vrele(*vpp);
	return (error);
}