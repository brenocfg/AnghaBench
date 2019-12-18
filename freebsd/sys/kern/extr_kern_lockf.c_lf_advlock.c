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
typedef  int /*<<< orphan*/  u_quad_t ;
struct vop_advlockasync_args {int /*<<< orphan*/ * a_cookiep; int /*<<< orphan*/ * a_task; int /*<<< orphan*/  a_flags; int /*<<< orphan*/  a_fl; int /*<<< orphan*/  a_op; int /*<<< orphan*/  a_id; int /*<<< orphan*/  a_vp; } ;
struct vop_advlock_args {int /*<<< orphan*/  a_flags; int /*<<< orphan*/  a_fl; int /*<<< orphan*/  a_op; int /*<<< orphan*/  a_id; int /*<<< orphan*/  a_vp; } ;
struct lockf {int dummy; } ;

/* Variables and functions */
 int lf_advlockasync (struct vop_advlockasync_args*,struct lockf**,int /*<<< orphan*/ ) ; 

int
lf_advlock(struct vop_advlock_args *ap, struct lockf **statep, u_quad_t size)
{
	struct vop_advlockasync_args a;

	a.a_vp = ap->a_vp;
	a.a_id = ap->a_id;
	a.a_op = ap->a_op;
	a.a_fl = ap->a_fl;
	a.a_flags = ap->a_flags;
	a.a_task = NULL;
	a.a_cookiep = NULL;

	return (lf_advlockasync(&a, statep, size));
}