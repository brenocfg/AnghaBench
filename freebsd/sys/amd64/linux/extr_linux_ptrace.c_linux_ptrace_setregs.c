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
struct thread {int dummy; } ;
struct reg {int dummy; } ;
struct linux_pt_reg {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  l_reg ;

/* Variables and functions */
 int /*<<< orphan*/  PT_SETREGS ; 
 int copyin (void*,struct linux_pt_reg*,int) ; 
 int kern_ptrace (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct reg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_regs_from_linux (struct reg*,struct linux_pt_reg*) ; 

__attribute__((used)) static int
linux_ptrace_setregs(struct thread *td, pid_t pid, void *data)
{
	struct reg b_reg;
	struct linux_pt_reg l_reg;
	int error;

	error = copyin(data, &l_reg, sizeof(l_reg));
	if (error != 0)
		return (error);
	map_regs_from_linux(&b_reg, &l_reg);
	error = kern_ptrace(td, PT_SETREGS, pid, &b_reg, 0);
	return (error);
}