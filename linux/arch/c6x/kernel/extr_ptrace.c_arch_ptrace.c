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
struct task_struct {int dummy; } ;

/* Variables and functions */
#define  PTRACE_POKETEXT 128 
 int /*<<< orphan*/  flush_icache_range (unsigned long,unsigned long) ; 
 int generic_ptrace_pokedata (struct task_struct*,unsigned long,unsigned long) ; 
 int ptrace_request (struct task_struct*,long,unsigned long,unsigned long) ; 

long arch_ptrace(struct task_struct *child, long request,
		 unsigned long addr, unsigned long data)
{
	int ret = 0;

	switch (request) {
		/*
		 * write the word at location addr.
		 */
	case PTRACE_POKETEXT:
		ret = generic_ptrace_pokedata(child, addr, data);
		if (ret == 0 && request == PTRACE_POKETEXT)
			flush_icache_range(addr, addr + 4);
		break;
	default:
		ret = ptrace_request(child, request, addr, data);
		break;
	}

	return ret;
}