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
struct trapframe {scalar_t__ srr0; } ;
struct thread {struct trapframe* td_frame; } ;
typedef  scalar_t__ register_t ;

/* Variables and functions */

int
ptrace_set_pc(struct thread *td, unsigned long addr)
{
	struct trapframe *tf;

	tf = td->td_frame;
	tf->srr0 = (register_t)addr;

	return (0);
}