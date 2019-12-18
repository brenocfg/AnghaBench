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
struct vop_reclaim_args {int /*<<< orphan*/  a_td; int /*<<< orphan*/  a_vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  unionfs_noderem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
unionfs_reclaim(struct vop_reclaim_args *ap)
{
	/* UNIONFS_INTERNAL_DEBUG("unionfs_reclaim: enter\n"); */

	unionfs_noderem(ap->a_vp, ap->a_td);

	/* UNIONFS_INTERNAL_DEBUG("unionfs_reclaim: leave\n"); */

	return (0);
}