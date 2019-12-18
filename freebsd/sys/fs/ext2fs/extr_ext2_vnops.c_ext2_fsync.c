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
struct vop_fsync_args {scalar_t__ a_waitfor; int /*<<< orphan*/  a_vp; } ;

/* Variables and functions */
 scalar_t__ MNT_WAIT ; 
 int ext2_update (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vop_stdfsync (struct vop_fsync_args*) ; 

__attribute__((used)) static int
ext2_fsync(struct vop_fsync_args *ap)
{
	/*
	 * Flush all dirty buffers associated with a vnode.
	 */

	vop_stdfsync(ap);

	return (ext2_update(ap->a_vp, ap->a_waitfor == MNT_WAIT));
}