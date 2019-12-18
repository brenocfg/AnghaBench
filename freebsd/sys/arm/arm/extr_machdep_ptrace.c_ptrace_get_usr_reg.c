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
typedef  int u_int ;
struct thread {TYPE_1__* td_frame; } ;
typedef  int register_t ;
struct TYPE_2__ {int tf_pc; int tf_usr_lr; int tf_usr_sp; int /*<<< orphan*/  tf_r0; } ;

/* Variables and functions */
#define  ARM_REG_NUM_LR 130 
#define  ARM_REG_NUM_PC 129 
#define  ARM_REG_NUM_SP 128 
 int /*<<< orphan*/  KASSERT (int,char*) ; 

__attribute__((used)) static u_int
ptrace_get_usr_reg(void *cookie, int reg)
{
	int ret;
	struct thread *td = cookie;

	KASSERT(((reg >= 0) && (reg <= ARM_REG_NUM_PC)),
	 ("reg is outside range"));

	switch(reg) {
	case ARM_REG_NUM_PC:
		ret = td->td_frame->tf_pc;
		break;
	case ARM_REG_NUM_LR:
		ret = td->td_frame->tf_usr_lr;
		break;
	case ARM_REG_NUM_SP:
		ret = td->td_frame->tf_usr_sp;
		break;
	default:
		ret = *((register_t*)&td->td_frame->tf_r0 + reg);
		break;
	}

	return (ret);
}