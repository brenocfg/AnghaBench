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
struct TYPE_3__ {int mc_vfp_size; int /*<<< orphan*/ * mc_vfp_ptr; } ;
struct TYPE_4__ {TYPE_1__ uc_mcontext; } ;
typedef  TYPE_2__ ucontext_t ;
struct ucontextx {int /*<<< orphan*/  mcontext_vfp; TYPE_2__ ucontext; } ;
struct arm_get_vfpstate_args {int mc_vfp_size; int /*<<< orphan*/ * mc_vfp; } ;
typedef  int /*<<< orphan*/  mcontext_vfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_GET_VFPSTATE ; 
 int sysarch (int /*<<< orphan*/ ,struct arm_get_vfpstate_args*) ; 

int
__fillcontextx2(char *ctx)
{
	struct ucontextx *ucxp;
	ucontext_t	 *ucp;
	mcontext_vfp_t	 *mvp;
	struct arm_get_vfpstate_args vfp_arg;

	ucxp = (struct ucontextx *)ctx;
	ucp = &ucxp->ucontext;
	mvp = &ucxp->mcontext_vfp;

	vfp_arg.mc_vfp_size = sizeof(mcontext_vfp_t);
	vfp_arg.mc_vfp = mvp;
	if (sysarch(ARM_GET_VFPSTATE, &vfp_arg) == -1)
			return (-1);
	ucp->uc_mcontext.mc_vfp_size = sizeof(mcontext_vfp_t);
	ucp->uc_mcontext.mc_vfp_ptr = mvp;
	return (0);
}