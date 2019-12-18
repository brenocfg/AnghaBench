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
struct vop_fdatasync_args {int /*<<< orphan*/  a_td; int /*<<< orphan*/  a_vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_WAIT ; 
 int VOP_FSYNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vop_stdfdatasync(struct vop_fdatasync_args *ap)
{

	return (VOP_FSYNC(ap->a_vp, MNT_WAIT, ap->a_td));
}