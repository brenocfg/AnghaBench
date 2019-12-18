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
typedef  void* u_long ;
struct trapframe {int /*<<< orphan*/  tf_spsr; void* tf_elr; void** tf_x; } ;
struct thread {struct trapframe* td_frame; } ;
struct image_params {void* entry_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSR_M_32 ; 
 int /*<<< orphan*/  memset (struct trapframe*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
freebsd32_setregs(struct thread *td, struct image_params *imgp,
   u_long stack)
{
	struct trapframe *tf = td->td_frame;

	memset(tf, 0, sizeof(struct trapframe));

	/*
	 * We need to set x0 for init as it doesn't call
	 * cpu_set_syscall_retval to copy the value. We also
	 * need to set td_retval for the cases where we do.
	 */
	tf->tf_x[0] = stack;
	/* SP_usr is mapped to x13 */
	tf->tf_x[13] = stack;
	/* LR_usr is mapped to x14 */
	tf->tf_x[14] = imgp->entry_addr;
	tf->tf_elr = imgp->entry_addr;
	tf->tf_spsr = PSR_M_32;
}