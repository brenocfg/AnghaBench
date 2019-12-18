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
typedef  int vm_ooffset_t ;
struct TYPE_2__ {int bo_bsize; } ;
struct vnode {TYPE_1__ v_bufobj; } ;
typedef  int daddr_t ;

/* Variables and functions */

__attribute__((used)) static daddr_t
ncl_gbp_getblkno(struct vnode *vp, vm_ooffset_t off)
{

	return (off / vp->v_bufobj.bo_bsize);
}