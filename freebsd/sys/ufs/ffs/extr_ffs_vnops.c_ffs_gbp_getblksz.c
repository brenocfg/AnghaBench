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
struct vnode {int /*<<< orphan*/  v_mount; } ;
typedef  int /*<<< orphan*/  daddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  um_fs; } ;

/* Variables and functions */
 TYPE_1__* VFSTOUFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VTOI (struct vnode*) ; 
 int blksize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ffs_gbp_getblksz(struct vnode *vp, daddr_t lbn)
{

	return (blksize(VFSTOUFS(vp->v_mount)->um_fs, VTOI(vp), lbn));
}