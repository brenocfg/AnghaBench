#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int tf_pc; int tf_r0; int /*<<< orphan*/  tf_spsr; int /*<<< orphan*/  tf_usr_sp; } ;
struct thread {struct trapframe* td_frame; } ;
struct TYPE_3__ {scalar_t__ ss_size; scalar_t__ ss_sp; } ;
typedef  TYPE_1__ stack_t ;

/* Variables and functions */
 int /*<<< orphan*/  PSR_USR32_MODE ; 
 int /*<<< orphan*/  STACKALIGN (scalar_t__) ; 

void
cpu_set_upcall(struct thread *td, void (*entry)(void *), void *arg,
	stack_t *stack)
{
	struct trapframe *tf = td->td_frame;

	tf->tf_usr_sp = STACKALIGN((int)stack->ss_sp + stack->ss_size);
	tf->tf_pc = (int)entry;
	tf->tf_r0 = (int)arg;
	tf->tf_spsr = PSR_USR32_MODE;
}