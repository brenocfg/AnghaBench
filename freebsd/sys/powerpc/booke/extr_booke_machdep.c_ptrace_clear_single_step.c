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
struct TYPE_3__ {int dbcr0; } ;
struct TYPE_4__ {TYPE_1__ booke; } ;
struct trapframe {TYPE_2__ cpu; int /*<<< orphan*/  srr1; } ;
struct thread {struct trapframe* td_frame; } ;

/* Variables and functions */
 int DBCR0_IC ; 
 int DBCR0_IDM ; 
 int /*<<< orphan*/  PSL_DE ; 

int
ptrace_clear_single_step(struct thread *td)
{
	struct trapframe *tf;

	tf = td->td_frame;
	tf->srr1 &= ~PSL_DE;
	tf->cpu.booke.dbcr0 &= ~(DBCR0_IDM | DBCR0_IC);
	return (0);
}