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
typedef  int /*<<< orphan*/  uint32_t ;
struct thread {TYPE_1__* td_frame; } ;
struct TYPE_2__ {int /*<<< orphan*/  tf_pc; } ;

/* Variables and functions */
 int EINVAL ; 
 int arm_predict_branch (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ inst_branch (int /*<<< orphan*/ ) ; 
 scalar_t__ inst_call (int /*<<< orphan*/ ) ; 
 scalar_t__ inst_return (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptrace_get_usr_int ; 
 int /*<<< orphan*/  ptrace_get_usr_reg ; 

__attribute__((used)) static int
ptrace_get_alternative_next(struct thread *td, uint32_t cur_instr,
    uint32_t *alt_next_address)
{
	int error;

	if (inst_branch(cur_instr) || inst_call(cur_instr) ||
	    inst_return(cur_instr)) {
		error = arm_predict_branch(td, cur_instr, td->td_frame->tf_pc,
		    alt_next_address, ptrace_get_usr_reg, ptrace_get_usr_int);

		return (error);
	}

	return (EINVAL);
}