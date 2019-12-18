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
struct thread {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  en_mxcsr; } ;
struct savexmm {TYPE_1__ sv_env; } ;
struct TYPE_4__ {struct savexmm sv_xmm; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PT_GETXMMREGS 134 
#define  PT_GETXSTATE 133 
#define  PT_GETXSTATE_INFO 132 
#define  PT_GETXSTATE_OLD 131 
#define  PT_SETXMMREGS 130 
#define  PT_SETXSTATE 129 
#define  PT_SETXSTATE_OLD 128 
 int copyin (void*,struct savexmm*,int) ; 
 int copyout (struct savexmm*,void*,int) ; 
 int /*<<< orphan*/  cpu_fxsr ; 
 int /*<<< orphan*/  cpu_mxcsr_mask ; 
 int cpu_ptrace_xstate (struct thread*,int,void*,int) ; 
 TYPE_2__* get_pcb_user_save_td (struct thread*) ; 
 int /*<<< orphan*/  npxgetregs (struct thread*) ; 

__attribute__((used)) static int
cpu_ptrace_xmm(struct thread *td, int req, void *addr, int data)
{
	struct savexmm *fpstate;
	int error;

	if (!cpu_fxsr)
		return (EINVAL);

	fpstate = &get_pcb_user_save_td(td)->sv_xmm;
	switch (req) {
	case PT_GETXMMREGS:
		npxgetregs(td);
		error = copyout(fpstate, addr, sizeof(*fpstate));
		break;

	case PT_SETXMMREGS:
		npxgetregs(td);
		error = copyin(addr, fpstate, sizeof(*fpstate));
		fpstate->sv_env.en_mxcsr &= cpu_mxcsr_mask;
		break;

	case PT_GETXSTATE_OLD:
	case PT_SETXSTATE_OLD:
	case PT_GETXSTATE_INFO:
	case PT_GETXSTATE:
	case PT_SETXSTATE:
		error = cpu_ptrace_xstate(td, req, addr, data);
		break;

	default:
		return (EINVAL);
	}

	return (error);
}