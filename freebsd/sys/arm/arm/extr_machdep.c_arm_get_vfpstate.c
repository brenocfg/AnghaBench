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
typedef  int /*<<< orphan*/  ua ;
struct thread {int dummy; } ;
struct arm_get_vfpstate_args {int mc_vfp_size; int /*<<< orphan*/  mc_vfp; } ;
typedef  int /*<<< orphan*/  mcontext_vfp_t ;
typedef  int /*<<< orphan*/  mcontext_vfp ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int copyin (void*,struct arm_get_vfpstate_args*,int) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_vfpcontext (struct thread*,int /*<<< orphan*/ *) ; 

int
arm_get_vfpstate(struct thread *td, void *args)
{
	int rv;
	struct arm_get_vfpstate_args ua;
	mcontext_vfp_t	mcontext_vfp;

	rv = copyin(args, &ua, sizeof(ua));
	if (rv != 0)
		return (rv);
	if (ua.mc_vfp_size != sizeof(mcontext_vfp_t))
		return (EINVAL);
#ifdef VFP
	get_vfpcontext(td, &mcontext_vfp);
#else
	bzero(&mcontext_vfp, sizeof(mcontext_vfp));
#endif

	rv = copyout(&mcontext_vfp, ua.mc_vfp,  sizeof(mcontext_vfp));
	if (rv != 0)
		return (rv);
	return (0);
}