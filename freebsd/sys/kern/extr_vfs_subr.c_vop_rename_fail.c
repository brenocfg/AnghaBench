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
struct vop_rename_args {int /*<<< orphan*/ * a_fvp; int /*<<< orphan*/ * a_fdvp; int /*<<< orphan*/ * a_tdvp; int /*<<< orphan*/ * a_tvp; } ;

/* Variables and functions */
 int /*<<< orphan*/  vput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vrele (int /*<<< orphan*/ *) ; 

void
vop_rename_fail(struct vop_rename_args *ap)
{

	if (ap->a_tvp != NULL)
		vput(ap->a_tvp);
	if (ap->a_tdvp == ap->a_tvp)
		vrele(ap->a_tdvp);
	else
		vput(ap->a_tdvp);
	vrele(ap->a_fdvp);
	vrele(ap->a_fvp);
}