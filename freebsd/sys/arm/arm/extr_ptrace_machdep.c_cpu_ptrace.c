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
typedef  int /*<<< orphan*/  vfp ;
struct thread {int dummy; } ;
typedef  int /*<<< orphan*/  mcontext_vfp_t ;

/* Variables and functions */
 int EINVAL ; 
#define  PT_GETVFPREGS 129 
#define  PT_SETVFPREGS 128 
 int copyin (void*,int /*<<< orphan*/ *,int) ; 
 int copyout (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  get_vfpcontext (struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_vfpcontext (struct thread*,int /*<<< orphan*/ *) ; 

int
cpu_ptrace(struct thread *td, int req, void *addr, int data)
{
#ifdef VFP
	mcontext_vfp_t vfp;
#endif
	int error;

	switch (req) {
#ifdef VFP
	case PT_GETVFPREGS:
		get_vfpcontext(td, &vfp);
		error = copyout(&vfp, addr, sizeof(vfp));
		break;
	case PT_SETVFPREGS:
		error = copyin(addr, &vfp, sizeof(vfp));
		if (error == 0)
			set_vfpcontext(td, &vfp);
		break;
#endif
	default:
		error = EINVAL;
	}

	return (error);
}