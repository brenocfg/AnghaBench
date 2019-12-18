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
struct vop_fsync_args {int /*<<< orphan*/  a_td; int /*<<< orphan*/  a_waitfor; TYPE_1__* a_vp; } ;
struct TYPE_2__ {scalar_t__ v_type; } ;

/* Variables and functions */
 scalar_t__ VREG ; 
 int ncl_flush (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_fsync(struct vop_fsync_args *ap)
{

	if (ap->a_vp->v_type != VREG) {
		/*
		 * For NFS, metadata is changed synchronously on the server,
		 * so there is nothing to flush. Also, ncl_flush() clears
		 * the NMODIFIED flag and that shouldn't be done here for
		 * directories.
		 */
		return (0);
	}
	return (ncl_flush(ap->a_vp, ap->a_waitfor, ap->a_td, 1, 0));
}