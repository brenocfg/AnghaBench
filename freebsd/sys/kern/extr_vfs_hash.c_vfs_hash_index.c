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
typedef  scalar_t__ u_int ;
struct vnode {TYPE_1__* v_mount; scalar_t__ v_hash; } ;
struct TYPE_2__ {scalar_t__ mnt_hashseed; } ;

/* Variables and functions */

u_int
vfs_hash_index(struct vnode *vp)
{

	return (vp->v_hash + vp->v_mount->mnt_hashseed);
}