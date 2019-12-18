#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vop_bmap_args {int /*<<< orphan*/ * a_bnp; int /*<<< orphan*/  a_runb; int /*<<< orphan*/  a_runp; int /*<<< orphan*/  a_bn; int /*<<< orphan*/  a_vp; int /*<<< orphan*/ ** a_bop; } ;
typedef  int /*<<< orphan*/  daddr_t ;
struct TYPE_4__ {int i_flag; TYPE_1__* i_devvp; } ;
struct TYPE_3__ {int /*<<< orphan*/  v_bufobj; } ;

/* Variables and functions */
 int IN_E4EXTENTS ; 
 TYPE_2__* VTOI (int /*<<< orphan*/ ) ; 
 int ext2_bmaparray (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ext4_bmapext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ext2_bmap(struct vop_bmap_args *ap)
{
	daddr_t blkno;
	int error;

	/*
	 * Check for underlying vnode requests and ensure that logical
	 * to physical mapping is requested.
	 */
	if (ap->a_bop != NULL)
		*ap->a_bop = &VTOI(ap->a_vp)->i_devvp->v_bufobj;
	if (ap->a_bnp == NULL)
		return (0);

	if (VTOI(ap->a_vp)->i_flag & IN_E4EXTENTS)
		error = ext4_bmapext(ap->a_vp, ap->a_bn, &blkno,
		    ap->a_runp, ap->a_runb);
	else
		error = ext2_bmaparray(ap->a_vp, ap->a_bn, &blkno,
		    ap->a_runp, ap->a_runb);
	*ap->a_bnp = blkno;
	return (error);
}