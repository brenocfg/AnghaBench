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
typedef  int /*<<< orphan*/  tmp ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DBG_MEM ; 
 long EIO ; 
 int /*<<< orphan*/  FOLL_FORCE ; 
#define  PTRACE_PEEKDATA 133 
#define  PTRACE_PEEKTEXT 132 
#define  PTRACE_PEEKUSR 131 
#define  PTRACE_POKEDATA 130 
#define  PTRACE_POKETEXT 129 
#define  PTRACE_POKEUSR 128 
 int /*<<< orphan*/  force_successful_syscall_return () ; 
 long generic_ptrace_pokedata (struct task_struct*,unsigned long,unsigned long) ; 
 long get_reg (struct task_struct*,unsigned long) ; 
 size_t ptrace_access_vm (struct task_struct*,unsigned long,unsigned long*,int,int /*<<< orphan*/ ) ; 
 long ptrace_request (struct task_struct*,long,unsigned long,unsigned long) ; 
 long put_reg (struct task_struct*,unsigned long,unsigned long) ; 

long arch_ptrace(struct task_struct *child, long request,
		 unsigned long addr, unsigned long data)
{
	unsigned long tmp;
	size_t copied;
	long ret;

	switch (request) {
	/* When I and D space are separate, these will need to be fixed.  */
	case PTRACE_PEEKTEXT: /* read word at location addr. */
	case PTRACE_PEEKDATA:
		copied = ptrace_access_vm(child, addr, &tmp, sizeof(tmp),
				FOLL_FORCE);
		ret = -EIO;
		if (copied != sizeof(tmp))
			break;
		
		force_successful_syscall_return();
		ret = tmp;
		break;

	/* Read register number ADDR. */
	case PTRACE_PEEKUSR:
		force_successful_syscall_return();
		ret = get_reg(child, addr);
		DBG(DBG_MEM, ("peek $%lu->%#lx\n", addr, ret));
		break;

	/* When I and D space are separate, this will have to be fixed.  */
	case PTRACE_POKETEXT: /* write the word at location addr. */
	case PTRACE_POKEDATA:
		ret = generic_ptrace_pokedata(child, addr, data);
		break;

	case PTRACE_POKEUSR: /* write the specified register */
		DBG(DBG_MEM, ("poke $%lu<-%#lx\n", addr, data));
		ret = put_reg(child, addr, data);
		break;
	default:
		ret = ptrace_request(child, request, addr, data);
		break;
	}
	return ret;
}