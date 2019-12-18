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
struct vop_inactive_args {TYPE_1__* a_vp; } ;
struct TYPE_2__ {int /*<<< orphan*/ * v_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  vrecycle (TYPE_1__*) ; 

__attribute__((used)) static int
unionfs_inactive(struct vop_inactive_args *ap)
{
	ap->a_vp->v_object = NULL;
	vrecycle(ap->a_vp);
	return (0);
}